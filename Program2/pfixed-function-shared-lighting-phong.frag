// Specifying version of GLSL. If the compiler does not support 
// this version of higher, an error will occur.
#version 330

#pragma optimize(off)
#pragma debug(on)

// Declare default precision - eliminates warnings (but can cause an error on some machines)
precision mediump float;

// Structure for holding general light properties
struct GeneralLight {
  
	vec4 ambientColor;		// ambient color of the light
	vec4 diffuseColor;		// diffuse color of the light
    vec4 specularColor;		// specular color of the light

	// Either the position or direction
	// if w = 0 then the light is directional and direction specified 
	// is the negative of the direction the light is shinning
	// if w = 1 then the light is positional
    vec4 positionOrDirection;    
					  
	// spotlight attributes
    vec3 spotDirection;		// the direction the cone of light is shinning    
	int isSpot;				// 1 if the light is a spotlight  
    float spotCutoffCos;	// Cosine of the spot cutoff angle
    float spotExponent;		// For gradual falloff near cone edge

	// attenuation coefficients
    float constant; 
    float linear;
    float quadratic;

	int enabled;			// 1 if light is "on"

};

// Structure for material properties
struct Material
{
	vec4 ambientMat;

	vec4 diffuseMat;

	vec4 specularMat;

	float specularExp;

	vec4 emissiveMat;

	bool textureMapped;
};

const int MaxLights = 8;

layout (std140) uniform LightBlock
{
 GeneralLight lights[MaxLights];
};


uniform Material object;

// Sampler to determine interpolated texture coordinates for the fragment 
uniform sampler2D gSampler;

layout (std140) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};

// Vertex attributes passed in by the vertex shader
//in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;  
in vec2 TexCoord0;

// Output color for the fragment (pixel)
out vec4 FragColor;

vec4 calcLight( GeneralLight light, Material object )
{
	vec4 totalLight = vec4(0.0f,0.0f,0.0f,1.0f);
	if(light.enabled == 1) {
		if(light.isSpot==1){
			//SpotLight

				// Find a unit vector that points at the
				// light source
				vec3 spotDirection = normalize(light.positionOrDirection.xyz - WorldPos0);

				vec3 spDir = normalize(light.spotDirection);
				float spotExponent =  dot(spDir,-spotDirection);

				if(dot(spDir,-spotDirection) > light.spotCutoffCos){
					// Diffuse
					float DiffuseFactor = max(dot(Normal0, spotDirection), 0.0f);
					totalLight += DiffuseFactor * object.diffuseMat * light.diffuseColor;

					// Specular
					vec3 PixelToEye = normalize(worldEyePosition - WorldPos0);

					vec3 LightReflect = normalize(reflect(-spotDirection, Normal0));

					float SpecularFactor = max(dot(PixelToEye, LightReflect), 0.0f);
				
					SpecularFactor = pow(SpecularFactor, object.specularExp);

					totalLight += SpecularFactor * object.specularMat * light.specularColor;

					float falloff= 1.0f - (1.0f - spotExponent) /(1.0f - light.spotCutoffCos);

					//float falloff = pow( spotExponent, 50.0f ); outdated code
					totalLight *= falloff;
				}
				//return totalLight;
		}

		totalLight = object.ambientMat * light.ambientColor;
		if((light.positionOrDirection[3] < 1.0f)){		
			//DirectionalLight

			// Find a unit vector that points at the
			// light source
			vec3 directionToDirectLight = normalize(light.positionOrDirection.xyz);

			// Diffuse
			float DiffuseFactor = max(dot(Normal0, directionToDirectLight), 0.0f);
			totalLight += DiffuseFactor * object.diffuseMat * light.diffuseColor;

			// Specular
			vec3 PixelToEye = normalize(worldEyePosition - WorldPos0);

			vec3 LightReflect = normalize(reflect(-directionToDirectLight, Normal0));

			float SpecularFactor = max(dot(PixelToEye, LightReflect), 0.0f);
		
			SpecularFactor = pow(SpecularFactor, object.specularExp);

			totalLight += SpecularFactor * object.specularMat * light.specularColor;
				
		}//EndDirectionalLight
		else{
			// Find a unit vector that points at the
			// light source
			vec3 directionToPosLight = normalize(light.positionOrDirection.xyz - WorldPos0);

			// Diffuse
			float DiffuseFactor = max(dot(Normal0, directionToPosLight), 0.0f);
			totalLight += DiffuseFactor * object.diffuseMat * light.diffuseColor;
			
			// Specular
			vec3 PixelToEye = normalize(worldEyePosition - WorldPos0);

			vec3 LightReflect = normalize(reflect(-directionToPosLight, Normal0));

			float SpecularFactor = max(dot(PixelToEye, LightReflect), 0.0f);
		
			SpecularFactor = pow(SpecularFactor, object.specularExp);

			totalLight += SpecularFactor * object.specularMat * light.specularColor;

			}
	}//end light on
	return totalLight;
}

const vec4 fogColor = vec4(0.8f, 0.8f, 0.8f, 0.8f);
const float fogEnd = 50.0f;
const float fogStart = 5.0f;
const float fogDensity = 0.01f;
float distanceFromViewPoint;
float linearFogFactor() 
{
	distanceFromViewPoint = distance(worldEyePosition, WorldPos0);
	return max((fogEnd - distanceFromViewPoint)/(fogEnd - fogStart), 0.0f);
}
float exponentialFogFactor() {
	distanceFromViewPoint = distance(worldEyePosition, WorldPos0);
	return exp( -(fogDensity * distanceFromViewPoint));
}
float exponentialTwoFogFactor() {
	distanceFromViewPoint = distance(worldEyePosition, WorldPos0);
	return exp( - pow((fogDensity * distanceFromViewPoint),2));
}

void main()
{
	Material texturedMaterial = object;
	if (object.textureMapped == true) {
		texturedMaterial.ambientMat = texture2D(gSampler, TexCoord0.st); 
		texturedMaterial.diffuseMat = texture2D(gSampler, TexCoord0.st); 
		texturedMaterial.specularMat = texture2D(gSampler, TexCoord0.st); 
	}
	FragColor = object.emissiveMat;
	for (int i = 0; i < MaxLights; i++) { 
		FragColor += calcLight( lights[i], texturedMaterial );
	}

	float fogFactor = exponentialFogFactor();

	FragColor = fogFactor * FragColor + (1-fogFactor) * fogColor;

}