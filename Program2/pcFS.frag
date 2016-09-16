// Targeting version 3.3 of GLSL. If the compiler does not support 
// 3.3 it will cause an error.
#version 330
// The rasterizer runs over all the pixels that are inside
// the point, line, or triangle. For each pixel the fragment shader is executed. 

// Usually the job of the fragment shader is to determine the 
// color of the fragment (pixel). In addition, the fragment shader 
// can discard the pixel altogether or change its Z value (which will
// impact the result of subsequent Z test).

out vec4 FragColor;
//in vec4 vertexColor0;
in vec3 Normal0;
in vec3 WorldPos0;

struct Material { 
	vec4 ambientMat; 
	vec4 diffuseMat; 
	vec4 specularMat; 
	float specularExp; 
	vec4 emissiveMat; 

};
uniform Material object;

 struct AmbientLight
{
	vec4 colorIntensity;
	bool enabled;
};
uniform AmbientLight ambLight;

 struct DirectionalLight
{
	vec4 colorIntensity;
	vec4 specularIntensity;
	vec3 direction;
	bool enabled;
};
uniform DirectionalLight directLight;

layout (std140) uniform worldEyeBlock {
	vec3 worldEyePosition;
};

struct PositionalLight
{
	vec4 colorIntensity;
	vec4 specularIntensity;
	vec3 position;
	//Attenuation atten;
	bool enabled;
};
uniform PositionalLight posLight;

struct SpotLight
{
	vec4 colorIntensity;
	vec4 specularIntensity;
	vec3 position;
	vec3 spotDirection;
	float spotCutoffCos;
	//Attenuation atten;
	bool enabled;
};
uniform SpotLight spLight;


void main()
{
	 vec4 totalAmbientLight = vec4(0.0f,0.0f,0.0f,1.0f);
	 vec4 totalDirectionLight = vec4(0.0f,0.0f,0.0f,1.0f);
	 vec4 totalPositionalLight = vec4(0.0f,0.0f,0.0f,1.0f);
	 vec4 totalSpotLight = vec4(0.0f,0.0f,0.0f,1.0f);

	if(ambLight.enabled == true) {
		totalAmbientLight = object.ambientMat * ambLight.colorIntensity;
	}

	// Point Light
	if(posLight.enabled == true) {

	// Find a unit vector that points at the
	// light source
	vec3 directionToPosLight = normalize(posLight.position - WorldPos0);

	// Diffuse
	float DiffuseFactor = max(dot(Normal0, directionToPosLight), 0.0f);
	totalPositionalLight += DiffuseFactor * object.diffuseMat * posLight.colorIntensity;
//PROBLEM IN CODE ABOVE!! (it makes errors whenever I change it to += which is what it is a)


	// Specular
	vec3 PixelToEye = normalize(worldEyePosition - WorldPos0);

	vec3 LightReflect = normalize(reflect(-directionToPosLight, Normal0));

	float SpecularFactor = max(dot(PixelToEye, LightReflect), 0.0f);
	
	SpecularFactor = pow(SpecularFactor, object.specularExp);

	totalPositionalLight += SpecularFactor * object.specularMat * posLight.specularIntensity;
	}//point light end

	//DirectionalLight
		if(directLight.enabled == true) {

	// Find a unit vector that points at the
	// light source
	vec3 directionToDirectLight = normalize(directLight.direction);

	// Diffuse
	float DiffuseFactor = max(dot(Normal0, directionToDirectLight), 0.0f);
	totalDirectionLight += DiffuseFactor * object.diffuseMat * directLight.colorIntensity;



	// Specular
	vec3 PixelToEye = normalize(worldEyePosition - WorldPos0);

	vec3 LightReflect = normalize(reflect(-directionToDirectLight, Normal0));

	float SpecularFactor = max(dot(PixelToEye, LightReflect), 0.0f);
	
	SpecularFactor = pow(SpecularFactor, object.specularExp);

	totalDirectionLight += SpecularFactor * object.specularMat * directLight.specularIntensity;
	}//EndDirectionalLight

	//SpotLight
	if(spLight.enabled == true) {

	// Find a unit vector that points at the
	// light source
	vec3 directionToSpotLight = normalize(spLight.position - WorldPos0);

	vec3 spDir = normalize(spLight.spotDirection);
	float spotCosFactor =  dot(spDir,-directionToSpotLight);

	if(dot(spDir,-directionToSpotLight) > spLight.spotCutoffCos){
		// Diffuse
		float DiffuseFactor = max(dot(Normal0, directionToSpotLight), 0.0f);
		totalSpotLight += DiffuseFactor * object.diffuseMat * spLight.colorIntensity;

		// Specular
		vec3 PixelToEye = normalize(worldEyePosition - WorldPos0);

		vec3 LightReflect = normalize(reflect(-directionToSpotLight, Normal0));

		float SpecularFactor = max(dot(PixelToEye, LightReflect), 0.0f);
	
		SpecularFactor = pow(SpecularFactor, object.specularExp);

		totalSpotLight += SpecularFactor * object.specularMat * spLight.specularIntensity;

		float falloff= 1.0f - (1.0f - spotCosFactor) /(1.0f - spLight.spotCutoffCos);

		//float falloff = pow( spotCosFactor, 50.0f ); outdated code
		totalSpotLight *= falloff;


	}
	}//point light end

	//EndSpotlight



	// Set the fragment to the diffuseMat color. 
	FragColor = totalAmbientLight + totalDirectionLight + totalPositionalLight + object.emissiveMat + totalSpotLight;
}