#include "SoundSource.h"

bool SoundSource::soundInitialized = false;

GLboolean OpenALInit()
{
	// Initialize Framework
	ALFWInit();
	if (!ALFWInitOpenAL())
	{
		ALFWprintf("Failed to initialize OpenAL\n");
		ALFWShutdown();
		return false;
	}
	else {
		return true;
	}
}

SoundSource::SoundSource(string soundFileName )
	:VisualObject( ), soundFileName(soundFileName)
{
	// Initialize OpenAL if it has not been initialized yet
	if ( SoundSource::soundInitialized == false ) {

		OpenALInit();
		SoundSource::soundInitialized = true;
	}

	// Load the sound 
	ALuint      uiBuffer;

	// Generate an AL Buffer
	alGenBuffers( 1, &uiBuffer );

	// Load Wave file into OpenAL Buffer
	if (!ALFWLoadWaveToBuffer(soundFileName.c_str(), uiBuffer)) {

		ALFWprintf("Failed to load %s.\n", soundFileName.c_str());
	}
	else {

		ALFWprintf("Loaded %s sound file.\n", soundFileName.c_str());
	
		// Generate a Source to playback the Buffer
		alGenSources( 1, &uiSource );

		// Attach Source to Buffer
		alSourcei( uiSource, AL_BUFFER, uiBuffer );
		
		// Set source properties
		alSourcef(uiSource, AL_PITCH, 1.0f); // pitch multiplier 
		alSourcef(uiSource, AL_GAIN, 1.0f); // source gain value 
	
		// determines if the positions are relative to the listener
		alSourcei(uiSource, AL_SOURCE_RELATIVE, AL_FALSE);

		// Position for sound sources
		alSource3f( uiSource, AL_POSITION, 0.0, 0.0, 0.0);

		// Velocity for sound sources
		alSource3f(uiSource, AL_VELOCITY, 0.0, 0.0, 0.0);

	}

} // end SoundSource constructor


SoundSource::~SoundSource(void)
{
	alDeleteSources( 1, &uiSource);

} // end SoundSource destructor


// Update this object and all of its children
void SoundSource::update(float elapsedTimeSeconds)
{
	vec3 pos = getWorldPosition();

	// Previous position used for velocity calculations
	static vec3 lastPosition = pos;

	// Position the sound source
	alSource3f( uiSource, AL_POSITION, pos.x, pos.y, pos.z);

	// Calculate the velocity of the soound source
	if ( elapsedTimeSeconds > 0.0f) {
		vec3 velocity  = (pos - lastPosition)/elapsedTimeSeconds;

		alSource3f(uiSource, AL_VELOCITY, velocity.x, velocity.y, velocity.z );

	}

	// Save position for next update
	lastPosition = pos;

	VisualObject::update(elapsedTimeSeconds);

} // end update

// Start playing the sound
void SoundSource::play()
{
	// Play the source
	alSourcePlay( uiSource);

} // end play

// Stop the sound. When played again, it will start from the beginning.
void SoundSource::stop()
{
	// Stop the source
	alSourceStop( uiSource);

} // end stop

// Pause the sound. When played again, it will start from the point 
// where is was paused.
void SoundSource::pause()
{
	// Pause the source
	alSourcePause( uiSource);

} // end pause


// Turn looping on and off
void SoundSource::setLooping(bool loopingOn)
{
	if(loopingOn) {
		// turns looping on
		alSourcei(uiSource, AL_LOOPING, AL_TRUE); 
	}
	else {
		// turns looping off	
		alSourcei(uiSource, AL_LOOPING, AL_FALSE); 
	}

} // end setLooping

// Check to see if a sound it actively playing
bool SoundSource::isPlaying()
{
	ALint playing; 
	alGetSourcei(uiSource, AL_SOURCE_STATE, &playing);

	if (playing == AL_PLAYING) {
		return true;
	}
	else {
		return false;
	}

} // end isPlaying