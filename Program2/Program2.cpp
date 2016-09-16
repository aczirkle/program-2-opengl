#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor2.h"
#include "Pyramid.h"
#include "SpinnerController.h"
#include "OrbitController.h"
#include "WaypointController.h"
#include "SharedGeneralLighting.h"

#include "SoundSource.h"

#include "Sphere.h"
#include "Cylinder.h"
#include "font.h"
#include "Cube.h"
#include "Cone.h"
#include "Wall.h"
#include "SpaceShip.h"
#include "Torus.h"
#include "Player.h"
#include "PlayerObj.h"
#include "PhysicsController.h"

class Program2 : public OpenGLApplicationBase
{
public:

	VisualObject *floor, *pyramid0, *pyramid1, *pyramid2, *pyramid3, *pyramid4;
	vector<VisualObject*> enemies;
	vector<VisualObject*> bullets;
	vector<VisualObject*> col;
	vector<SpinnerController*> spinners;
	vector<VisualObject*> plbullets;
	SharedGeneralLighting generalLighting;
	VisualObject* obj;
	Player* pl;
	PlayerObj* plo;
	int yCur, xCur, fuel,score,lives;
	bool running,win, lose;
	GLuint shaderProgram;
	//SoundSource* jet;
	GLuint shaderProgramTorus;
	

	Program2() : view(7), rotationX(0.0f), rotationY(0.0f), zTrans(-12.0f)
	{
		ShowCursor(FALSE);	
		glutFullScreenToggle();
		running=false;
		win=false;
		lose=false;
		
		glutPassiveMotionFunc(passiveMouse);
		// Create array of ShaderInfo structs that specifies the vertex and 
		// fragment shaders to be compiled and linked into a program. 
		ShaderInfo shaders[] = { 
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" }, 
			{ GL_FRAGMENT_SHADER, "pcFS.frag"}, 
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};

		ShaderInfo shaders2[] = { 
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" }, 
			{ GL_FRAGMENT_SHADER, "pfixed-function-shared-lighting-phong.frag"}, 
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};

		// Read the files and create the OpenGL shader program. 
		shaderProgram = BuildShaderProgram(shaders2);
		shaderProgramTorus = BuildShaderProgram(shaders);
		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		generalLighting.setUniformBlockForShader( shaderProgram );
	
		floor = new Floor2(100);
		floor->setShader(shaderProgram);
		floor->material.setTextureMapped(true); 
		floor->material.setupTexture("fetch.bmp");
		addChild(floor);
		fuel=1000;
		score=0;
		lives=3;
		//counter=0;

		pyramid0 = new SpaceShip();//new Pyramid();
		pyramid0->setShader(shaderProgram);
		//pyramid0->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, -3.0f, -4.0f)); 
		pyramid0->material.setAmbientAndDiffuseMat(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		pyramid0->material.setTextureMapped(true); 
		pyramid0->material.setupTexture(".bmp");
		addChild(pyramid0);

	/*	Torus* t = new Torus(vec4(0.0f,0.f,1.0f,0.0f),.1f,1.0f,10,16);
		t->addController(new OrbitController(glm::vec3(10.f, 0.f, 0.f), glm::vec3(0.f, -1.f, 0.f), glm::vec3(1.f, 0.f, 0.f),35));
		t->material.setAmbientAndDiffuseMat(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		t->setShader(shaderProgramTorus);
		t->material.setEmissiveMat(glm::vec4(0.0f, 1.0f, .0f, .1f));
		addChild(t);*/

		//pl = new Player(vec4(2,0,2,1),10,5);
		//addChild(pl);
		plo = new PlayerObj(vec3(0,0,12),vec3(0,1,0),20);
		pyramid0->addController(plo);

	

		Wall* wall = new Wall(); 
		wall->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, -3.0f, -50.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(50.0f));; 
		wall->setShader(shaderProgram); 
		wall->material.setTextureMapped(true); 
		wall->material.setupTexture("sky.bmp");
		addChild(wall);
		wall = new Wall(); 
		wall->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, -3.0f, 50.0f)) * glm::rotate(glm::mat4(1),180.f,vec3(0,1,0)) *glm::scale(glm::mat4(1.0f), glm::vec3(50.0f));
		wall->setShader(shaderProgram); 
		wall->material.setTextureMapped(true); 
		wall->material.setupTexture("sky.bmp");
		addChild(wall);
		wall = new Wall(); 
		wall->fixedTransformation = glm::rotate(glm::mat4(1),90.f,vec3(0,1,0)) *translate(mat4(1.0f), vec3(0.0f, -3.0f, -50.0f)) *  glm::scale(glm::mat4(1.0f), glm::vec3(50.0f));
		wall->setShader(shaderProgram); 
		wall->material.setTextureMapped(true); 
		wall->material.setupTexture("sky.bmp");
		addChild(wall);
		wall = new Wall(); 
		wall->fixedTransformation = glm::rotate(glm::mat4(1),270.f,vec3(0,1,0)) *translate(mat4(1.0f), vec3(0.0f, -3.0f, -50.0f)) *  glm::scale(glm::mat4(1.0f), glm::vec3(50.0f));
		wall->setShader(shaderProgram); 
		wall->material.setTextureMapped(true); 
		wall->material.setupTexture("sky.bmp");
		addChild(wall);

		wall = new Wall(); 
		wall->fixedTransformation = glm::rotate(glm::mat4(1),90.f,vec3(1,0,0)) *translate(mat4(1.0f), vec3(0.0f, -3.0f, 50.0f)) *  glm::scale(glm::mat4(1.0f), glm::vec3(50.0f));;
		wall->setShader(shaderProgram); 
		wall->material.setTextureMapped(true); 
		wall->material.setupTexture("sky.bmp");
		addChild(wall);

	//	addChild(wall);
		int winWid =glutGet(GLUT_SCREEN_WIDTH) ;
		int winHei = glutGet(GLUT_SCREEN_HEIGHT);
		
		glutWarpPointer(winWid/2, winHei/2);
//		pl = new Player(vec4(0,0,0,0),0,20);

		spawnEnemies();
		spawnCollection();
		//pl->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.0f, 12.0f)); 
		//addChild(pl);



		SoundSource* s = new SoundSource("music.wav");
		s->setLooping(true);
		s->play();
		setupLighting();


	} // end  constructor

	GLuint enabledLoc, directOnLoc, posOnLoc, spotOnLoc;
	bool ambOn, directOn, posOn, spotOn;

	void fire(){
		if(running && plbullets.size()<3){
		VisualObject* tem0= new Cylinder(2,.1f,4,16);
		vec3 po = plo->posit();
		//PhysicsController* pys= new PhysicsController(plo->posit(),vec3(0,0,5),vec3(0,0,5),0);
		PhysicsController* pys= new PhysicsController(vec3(po.x,po.y,po.z),vec3(0,0,5),vec3(0,0,5),0);
		tem0->setShader(shaderProgram);
		tem0->material.setTextureMapped(true); 
		tem0->material.setupTexture("lazer.bmp");
		tem0->addController( pys);
		//glm::mat4 viewMatrix= glm::translate(glm::mat4(1.0f),);
		//glm::vec3 wep = viewMatrix[3].xyz;
		
		
		//pys->launch(vec3(po.x,po.y,po.z), plo->rotpos/*vec3(-po.x,po.y,-po.z)/*vec3(0,0,-1)*/,5.0f);

		vec3 pos = pyramid0->getWorldPosition();
				tem0->fixedTransformation = glm::rotate( glm::mat4(1.0f),fmod(plo->rotpos.y+90, 360.0f),vec3(0,1,0));
				//glm::rotate( glm::mat4(1.0f),fmod(rotation, 360.0f),axis);
				pys->launch(vec3(po.x,po.y,po.z),glm::rotate( glm::mat4(1.0f),fmod(-plo->rotpos.y+90, 360.0f),vec3(0,1,0))[0].xyz ,5.0f);

		addChild(tem0);
		plbullets.push_back(tem0);
		tem0->initialize();
		SoundSource* s = new SoundSource("lazer.wav");
		s->play();
		
		//pys->launch(glm::vec3(0,0,12),glm::vec3(0,0,-1),20.f);
		//tem0->addController( new PointPoint(posX,posY,posZ));
		
		}
	}
	   void enemyFire(){
			if(running){
				for(unsigned int i=0;i<enemies.size();i++){
		VisualObject* tem0= new Cylinder(2,.1f,4,16);
//		cout<<"Got called 1"<<endl;
		PhysicsController* pys= new PhysicsController(obj->getWorldPosition(),vec3(0,0,5),vec3(0,0,5),0);
		tem0->setShader(shaderProgram);
		tem0->material.setTextureMapped(true); 
		tem0->material.setupTexture("lazer.bmp");
		tem0->addController( pys);

		vec3 pos = obj->getWorldPosition();
		SpinnerController* sp= spinners.at(i);
//		cout<<"Got called 2"<<endl;
				tem0->fixedTransformation = glm::rotate( glm::mat4(1.0f),fmod(sp->rotation+90, 360.0f),vec3(0,1,0));
				//glm::rotate( glm::mat4(1.0f),fmod(rotation, 360.0f),axis);
				pys->launch(vec3(pos.x,pos.y,pos.z),glm::rotate( glm::mat4(1.0f),fmod(sp->rotation, 360.0f),vec3(0,1,0))[0].xyz ,5.0f);
			addChild(tem0);
			bullets.push_back(tem0);
			tem0->initialize();
		
				}
			}
		
	}
	   void spawnEnemies(){
		   Sphere* ene;
		   for(int i=0;i<15;i++){
				ene= new Sphere();
				ene->setShader(shaderProgram);
				ene->material.setAmbientAndDiffuseMat(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
				//ene->material.setEmissiveMat(glm::vec4(1.0f, 1.0f, .0f, 1.0f)); ///setting a base color which shows up in the dark, not a light
				ene->material.setTextureMapped(true); 
				ene->material.setupTexture("star.bmp");
				ene->fixedTransformation = glm::rotate(glm::mat4(1.0f),-90.0f,glm::vec3(1,0,0));
				//srand(5);
				int x = rand()%80;
				int z= rand()%80;
				int y=rand()%30;
				while((x<5 &&x>-5)||(y<5) || (z<5 &&z>-5)){
					x = rand()%80-45;
					y= rand()%30;
					z= rand()%80-45;
				}
				SpinnerController* s = new SpinnerController(vec3(x, y, z), glm::vec3(0.0f, 1.0f, 0.0f));
				ene->addController(s);
				spinners.push_back(s);
				addChild(ene);
				enemies.push_back(ene);
		   }
	   }
		void spawnCollection(){
		   Cube* ene;
		  
		   for(int i=0;i<15;i++){
			   //goodCube();
				ene= new Cube();
				ene->setShader(shaderProgram);
				ene->material.setAmbientAndDiffuseMat(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
				//ene->material.setEmissiveMat(glm::vec4(1.0f, 1.0f, .0f, 1.0f)); ///setting a base color which shows up in the dark, not a light
				ene->material.setTextureMapped(true); 
				ene->material.setupTexture("box.bmp");
				ene->fixedTransformation = glm::rotate(glm::mat4(1.0f),-90.0f,glm::vec3(1,0,0));
				int x = rand()%90-45;
				int z= rand()%90-45;
				int y=rand()%45;
				while((x<5 &&x>-5)||(y<5) || (z<5 &&z>-5)){
					x = rand()%90;
					y= rand()%30;
					z= rand()%90;
				}
				ene->addController(new SpinnerController(vec3(x, y, z), glm::vec3(0.0f, 1.0f, 0.0f)));
				addChild(ene);
				col.push_back(ene);
		   }
	   }
	   void goodCube(){
		   Cube* ene;
		   ene= new Cube();
				ene->setShader(shaderProgram);
				ene->material.setAmbientAndDiffuseMat(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
				//ene->material.setEmissiveMat(glm::vec4(1.0f, 1.0f, .0f, 1.0f)); ///setting a base color which shows up in the dark, not a light
				ene->material.setTextureMapped(true); 
				ene->material.setupTexture("box.bmp");
				ene->fixedTransformation = glm::rotate(glm::mat4(1.0f),-90.0f,glm::vec3(1,0,0));
				ene->addController(new SpinnerController(vec3(0, 0, 22), glm::vec3(0.0f, 1.0f, 0.0f)));
				addChild(ene);
				col.push_back(ene);
	   }

		void checkBad(){
			vec3 plpos=plo->posit();
			plpos = vec3(plpos.x,plpos.y,-plpos.z);
			unsigned int size=enemies.size();
		for (unsigned int i = 0; i <  size; i++) {
			if(close(plpos,enemies.at(i)->getWorldPosition())){
				enemies.at(i)->detachFromParent();
				enemies.erase(enemies.begin()+i);
				SoundSource* s = new SoundSource("ATAT.wav");
				s->play();
				plo->respawn();
				for(unsigned int q=0;bullets.size();q++){
					bullets.at(q)->detachFromParent();
					bullets.erase(bullets.begin()+i);
				}
				fuel=1000;
				lives--;
				if(lives<=0){
					running = false;
					lose=true;
				}
			}
			if(enemies.at(i)->getWorldPosition().z<=-50 || enemies.at(i)->getWorldPosition().z>=50 ||enemies.at(i)->getWorldPosition().x<=-50 || enemies.at(i)->getWorldPosition().x>=50 ){
				enemies.at(i)->detachFromParent();
				enemies.erase(enemies.begin()+i);
			}
			
		}
		size=bullets.size();

		for (unsigned int i = 0; i <  size; i++) {
			if(close(plpos,bullets.at(i)->getWorldPosition())){
				bullets.at(i)->detachFromParent();
				bullets.erase(bullets.begin()+i);
				SoundSource* s = new SoundSource("ATAT.wav");
				s->play();
				for(unsigned int q=0;bullets.size();q++){
					bullets.at(q)->detachFromParent();
  					bullets.erase(bullets.begin()+i);
				}
				plo->respawn();
				lives--;
				fuel  =1000;
				if(lives<=0){
					lose=true;
					running=false;
				}
			}
			if(bullets.at(i)->getWorldPosition().z<=-50 || bullets.at(i)->getWorldPosition().z>=50 ||bullets.at(i)->getWorldPosition().x<=-50 || bullets.at(i)->getWorldPosition().x>=50 ){
				bullets.at(i)->detachFromParent();
				bullets.erase(bullets.begin()+i);
			}
			
		}

	}

		void checkGood(){
			vec3 plpos=plo->eye;
			plpos = vec3(-plpos.x,plpos.y,-plpos.z);
			unsigned int size = col.size();
			for (unsigned int i = 0; i <  size; i++) {
				if(close(plpos,col.at(i)->getWorldPosition())){
						col.at(i)->detachFromParent();
						col.erase(col.begin()+i);
						score++;
						SoundSource* s = new SoundSource("score.wav");
						s->play();
				}
			}
			size = enemies.size();
			for(unsigned int j=0;j<plbullets.size();j++){
				for (unsigned int i = 0; i <  size; i++) {
					if(close(enemies.at(i)->getWorldPosition(),plbullets.at(j)->getWorldPosition())){
						enemies.at(i)->detachFromParent();
						enemies.erase(enemies.begin()+i);
						plbullets.at(j)->detachFromParent();
						plbullets.erase(plbullets.begin()+j);
				}
			}
			}
		}	
		bool close(vec3 pl, vec3 el){
		//glm::vec3 id=children[i]->getWorldPosition();
		//glm::vec3 jd=children[j]->getWorldPosition();
		if(/*i!=j*/pl!=el && sqrt(pow(pl.x-el.x,2) +pow(pl.y-el.y,2)+pow(pl.z-el.z,2))<3)
			return true;
		return false;
	}


	   virtual void draw(){
		VisualObject::draw();
		int winWid =glutGet(GLUT_SCREEN_WIDTH) ;
		int winHei = glutGet(GLUT_SCREEN_HEIGHT);
		if(running){
		screenTextOutput( 5, 20- winWid, "Hit", vec4(0,0,0,1));
		screenTextOutput( winWid/2+10,winHei/2+20,"|",vec4(1.f,0.5f,0,1));
		screenTextOutput( winWid/2+10,winHei/2-20,"|",vec4(1.f,.5f,0,1));
		screenTextOutput( winWid/2-40,winHei/2,"---",vec4(1.f,.5f,0,1));
		screenTextOutput( winWid/2+20,winHei/2,"---",vec4(1.f,.5f,0,1));
		screenTextOutput( 20,winHei/2+20,"Fuel Remaining: "+to_string((long long)fuel),vec4(1.f,.5f,0,1));
		screenTextOutput( 20,winHei/2,"Boxes collected: "+to_string((long long)score),vec4(1.f,.5f,0,1));
		screenTextOutput( 20,winHei/2-20,"Lives Remaining: "+to_string((long long)lives),vec4(1.f,.5f,0,1));
		}
		else{
			if(win){
				screenTextOutput( winWid/2,winHei/2, "Congratulations you found your supplies! ", vec4(1.f,.5f,0,1));
			}
			else {
				if(lose){screenTextOutput( winWid/2-50,winHei/2, "Aww you died, Press enter to play again", vec4(1.f,.5f,0,1));
				}
			else{
			screenTextOutput( winWid/2-50,winHei/2+20, "Your supplies have been lost and mixed with a bunch of junk!", vec4(1.f,.5f,0,1));
			screenTextOutput( winWid/2-50,winHei/2, "Find them quickly as the empire has setup turrets here", vec4(1.f,.5f,0,1));
			screenTextOutput( winWid/2-50,winHei/2-20, "Press enter to Begin", vec4(1.f,.5f,0,1));
			screenTextOutput( winWid/2-50,winHei/2-40, "Controls: wasd standard, 'r' to raise and 'f' to fall k to hover", vec4(1.f,.5f,0,1));
			}
		}

	}
	   }

	void setupLighting() {
	// ***** Ambient Light **************
		generalLighting.setEnabled( GL_LIGHT_ZERO, true );
		generalLighting.setAmbientColor( GL_LIGHT_ZERO,
		vec4(0.2f, 0.2f, 0.2f, 1.0f));
		// ***** Directional Light ****************
		generalLighting.setEnabled( GL_LIGHT_ONE, false );
		generalLighting.setDiffuseColor( GL_LIGHT_ONE,
		vec4(0.75f, 0.75f, 0.75f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_ONE,
		vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_ONE,
		vec4(1.0f, 1.0f, 1.0f, 0.0f) );
		// ***** Positional Light ***************
		generalLighting.setEnabled( GL_LIGHT_TWO, false );
		generalLighting.setDiffuseColor( GL_LIGHT_TWO,
		vec4(0.5f, 0.5f, 0.5f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_TWO,
		vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_TWO,
		vec4(1.0f, 3.0f, 1.0f, 1.0f) );
		// ***** Spot Light **************
		generalLighting.setEnabled( GL_LIGHT_THREE, false );
		generalLighting.setIsSpot( GL_LIGHT_THREE, true );
		generalLighting.setDiffuseColor( GL_LIGHT_THREE,
		vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_THREE,
		vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_THREE,
		vec4(0.0f, 8.0f, 0.0f, 1.0f) );
		generalLighting.setSpotDirection( GL_LIGHT_THREE,
		vec3(0.0f, -1.0f, 0.0f) );
		generalLighting.setSpotCutoffCos( GL_LIGHT_THREE,
		cos(glm::radians(15.0f)) );
	} // end setUpLighting
	friend void passiveMouse(int x, int y);
	friend void viewMenu(int value);
	friend void SpecialKeyboardCB(int Key, int x, int y);
	int view;
	GLfloat rotationX, rotationY, zTrans;

	void KeyboardCB(unsigned char Key, int x, int y) 
	{
		GLfloat rotationValue = 0.5f;
		bool lightOn;
		switch (Key) {
		case '1':
			if (pyramid0->getParent() == NULL)
				this->addChild(pyramid0);
			else pyramid0->detachFromParent();
			break;
		case '2':
			if (pyramid1->getParent() == NULL)
				this->addChild(pyramid1);
			else pyramid1->detachFromParent();
			break;
		case '3':
			if (pyramid2->getParent() == NULL)
				this->addChild(pyramid2);
			else pyramid2->detachFromParent();
			break;
		case '4':
			if (pyramid3->getParent() == NULL)
				this->addChild(pyramid3);
			else pyramid3->detachFromParent();
			break;
		case '5':
			if (pyramid4->getParent() == NULL)
				this->addChild(pyramid4);
			else pyramid4->detachFromParent();
			break;
		case 13:
			running = true;
			lives=3;
			lose=false;
			win=false;
			score=0;
			goodCube();
			plo->respawn();
			break;
		case 'm':
			cout<<"X: "<<plo->posit().x<<endl;
			cout<<"Y: "<<plo->posit().y<<endl;
			cout<<"Z: "<<plo->posit().z<<endl;
			cout<<"Xeye: "<<to_string(static_cast<long long>(plo->eye.x))<<endl;
			cout<<"Yeye: "<<to_string(static_cast<long long>(plo->eye.y))<<endl;
			cout<<"Zeye: "<<to_string(static_cast<long long>(plo->eye.z))<<endl;
			cout<<"boxPosX: "<<to_string(static_cast<long long>(pyramid0->getWorldPosition().x))<<endl;
			cout<<"boxPosY: "<<to_string(static_cast<long long>(pyramid0->getWorldPosition().y))<<endl;
			cout<<"boxPosZ: "<<to_string(static_cast<long long>(pyramid0->getWorldPosition().z))<<endl;
			break;
		case 'x':
			plo->jump();
			break;
		case 'w' :
			//zTrans += rotationValue;
			plo->moveForward();
			break;
		case 's':
			//zTrans -= rotationValue;
			plo->moveBackward();
			break;
		case 'z':
			//plo->rotatePosZ();
			break;
		case 'c':
			//plo->rotateNegZ();
			break;
		case 'r' :
			//zTrans += rotationValue;
			if(running &&fuel>0){
			fuel=fuel-5;
			plo->moveUp();
			SoundSource* jet = new SoundSource("jet.wav");
			jet->play();
			}
			break;
		case 'f':
			//zTrans -= rotationValue;
			plo->moveDown();
			break;
		case 'k':
			plo->ack();
			break;
		case ' ':
			fire();
			//enemyFire(pyramid1);
			break;
		case 'a':
			//lightOn = generalLighting.getEnabled( GL_LIGHT_ZERO );
			//generalLighting.setEnabled( GL_LIGHT_ZERO, !lightOn );
		plo->moveLeft();
			break;
		case 'd':
			//lightOn = generalLighting.getEnabled( GL_LIGHT_ONE );
			//generalLighting.setEnabled( GL_LIGHT_ONE, !lightOn );
			plo->moveRight();
			break;
		case 'p':
			lightOn = generalLighting.getEnabled( GL_LIGHT_TWO );
			generalLighting.setEnabled( GL_LIGHT_TWO, !lightOn );
			break;
		case 'l':
			lightOn = generalLighting.getEnabled( GL_LIGHT_THREE );
			generalLighting.setEnabled( GL_LIGHT_THREE, !lightOn );
			break;
		default:
			OpenGLApplicationBase::KeyboardCB(Key, x, y);
		}
	}

	void checkMouse(){
	int centerX = glutGet(GLUT_SCREEN_WIDTH) / 2;
	int centerY = glutGet(GLUT_SCREEN_HEIGHT) / 2;
	if(xCur>centerX+200)
			plo->rotatePosY();
	if(xCur<centerX-200)
			plo->rotateNegY();
	if(xCur>(centerX+500)||xCur<centerX-500){
		glutWarpPointer(centerX, centerY);

	}
	/*if(yCur>centerY+100)
			plo->rotateLeft();
	if(yCur<centerY-100)
			plo->rotateRight();*/
	if(yCur>(centerY+400)||yCur<centerY-400){
		glutWarpPointer(centerX, centerY);
	}

}
	void setupMenus()
	{
		// Create polygon submenu
		GLuint menu0id = createViewMenu();
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createFrontFaceMenu();
		GLuint menu3id = createPointSizeMenu();
		GLuint menu4id = createLineWidthMenu();
		GLuint menu5id = createAntiAliasingMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("View", menu0id);
		glutAddSubMenu("Polygon Mode", menu1id);
		glutAddSubMenu("Rendered Polygon Face", menu2id);
		glutAddSubMenu("Point Size", menu3id);
		glutAddSubMenu("Line Width", menu4id);
		glutAddSubMenu("Anti-aliasing", menu5id);
		glutAddMenuEntry("Quit", 1); //Quit identifier.
		glutAttachMenu(GLUT_RIGHT_BUTTON);//Menu responds to right button
	}

	virtual void initialize()
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);

		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		
		VisualObject::initialize();
		glutSpecialFunc(SpecialKeyboardCB);

		setupMenus();
	} // end initialize

	// Update scene objects inbetween frames 
	virtual void update( float elapsedTimeSec ) 
	{ 
		static int counter;
		if( running){
			if(score>0){
				win=true;
				running=false;
			}
		if((int)elapsedTimeSec%1000==0 && fuel !=1000)
			fuel++;
		if(counter!=50){
			counter++;		
			checkGood();
		checkBad();
		checkMouse();
		
		}
		else{
			if(enemies.size()>1){
			int r = rand()%enemies.size();
			obj = enemies.at(r);
			enemyFire();
			}
		counter=0;
		}
		}
		changeView();
		//setViewPoint();
		
		//cout<<"boxPosX: "<<to_string(static_cast<long long>(pyramid0->getWorldPosition().x))<<endl;
			//cout<<"boxPosY: "<<to_string(static_cast<long long>(pyramid0->getWorldPosition().y))<<endl;
			//cout<<"boxPosZ: "<<to_string(static_cast<long long>(pyramid0->getWorldPosition().z))<<endl;
		VisualObject::update(elapsedTimeSec);
	} // end update

	virtual void setViewPoint() 
	{
		glm::mat4 viewMatrix;
		//mat4 rotx = glm::rotate( glm::mat4(1.0f),fmod(plo->heading.x, 360.0f),vec3(plo->rotpos.x));
	//mat4 roty = glm::rotate( glm::mat4(1.0f),fmod(plo->heading.y, 360.0f),vec3(0,plo->rotpos.y,0));
	//mat4 rotz = glm::rotate( glm::mat4(1.0f),fmod(plo->heading.z, 360.0f),vec3(0,0,plo->rotpos.z));
	//.setViewMatrix( (glm::translate(glm::mat4(1.f),plo->position))* rotx*roty*roty);
		/*switch (view) {
		case 0:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3( 0.0f, 0.0f, -12 ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 1:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3( 0.0f, 0.0f, -10 ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 2:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3( 0.0f, 0.0f, -10 )) * glm::rotate(glm::mat4(1.0f), fmod(45.0f, 360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 3:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3( 0.0f, 0.0f, -10 )) * glm::rotate(glm::mat4(1.0f), fmod(90.0f, 360.0f), glm::vec3(1.0f, 0.0f, 0.0f))
				* glm::rotate(glm::mat4(1.0f), fmod(90.0f, 360.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 4:
			viewMatrix = glm::lookAt(glm::vec3(0.f, 0.f, 10), glm::vec3(0,0,0), glm::vec3(0, 1,0 ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 5:
			viewMatrix = glm::lookAt(glm::vec3(0.f, 7.1f, 7.1f), glm::vec3(0,0,0), glm::vec3(0, 1,0 ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 6:
			viewMatrix = glm::lookAt(glm::vec3(0.f, 10.f, 0), glm::vec3(0,0,0), glm::vec3(1,0, 0 ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 7:
			glm::mat4 transView = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, zTrans ));
			glm::mat4 rotateViewX = glm::rotate(glm::mat4(1.0f), rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotateViewY = glm::rotate(glm::mat4(1.0f), rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix( transView * rotateViewX * rotateViewY );
		}*/

	}
void changeView(){

	glm::mat4 transView = glm::translate(glm::mat4(1.0f), glm::vec3(-plo->position.x, -plo->position.y, -plo->position.z ));
	glm::mat4 rotateViewX = glm::rotate(glm::mat4(1.0f), plo->rotpos.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotateViewY = glm::rotate(glm::mat4(1.0f), plo->rotpos.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotateViewZ = glm::rotate(glm::mat4(1.0f), plo->rotpos.z, glm::vec3(0.0f, 0.0f, 1.0f));
	projectionAndViewing.setViewMatrix(( transView * rotateViewX * rotateViewY* rotateViewZ));
}

protected:
	GLuint createViewMenu()
	{
		GLuint menuId = glutCreateMenu(viewMenu);
		// Specify menu items and their integer identifiers
		glutAddMenuEntry("Default", 0);
		glutAddMenuEntry("View 1", 1);
		glutAddMenuEntry("View 2", 2);
		glutAddMenuEntry("View 3", 3);
		glutAddMenuEntry("View 4", 4);
		glutAddMenuEntry("View 5", 5);
		glutAddMenuEntry("View 6", 6);
		glutAddMenuEntry("View 7", 7);


		return menuId;
	}

};
Program2* labClassPtr;
int main(int argc, char** argv) 
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Program 2" );

	Program2 pApp;

	labClassPtr = &pApp;
	GLUTBaseRunApplication(&pApp);

}

void viewMenu (int value)
{
	labClassPtr-> view = value;
	cout << "View point " << value << endl;
} // end viewMenu

void SpecialKeyboardCB(int Key, int x, int y)
{
	GLfloat rotationValue = 0.5f;
	switch (Key) {
	case GLUT_KEY_RIGHT:
		labClassPtr->rotationY +=rotationValue;
		break;
	case GLUT_KEY_LEFT:
		labClassPtr->rotationY -=rotationValue;
		break;
	case GLUT_KEY_UP:
		labClassPtr->rotationX += rotationValue;
		break;
	case GLUT_KEY_DOWN:
		labClassPtr->rotationX -= rotationValue;
		break;
	default:
		break;
	}
	
}

void passiveMouse(int x, int y){
	labClassPtr->xCur=x;
	labClassPtr->yCur=y;

}