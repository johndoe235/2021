#ifndef __SDL_LOADER__
#define __SDL_LOADER__

/* C system includes */

/* C++ system includes */

/* Third-party includes */

/* Own includes */

/* Forward Declaration */

/*                    */

enum  SDLInitFlags
{
	TIMER= 0x00000001u,
	AUDIO= 0x00000010u,
	VIDEO= 0x00000020u,
	JOYSTICK =0x00000200u,
	HAPTIC =0x00001000u,
	GAMECONTROLLER= 0x00002000u,
	EVENTS =0x00004000u,
	SENSORS =0x00008000u,
	NOPARACHUTE= 0x00100000u,
	EVERYTHING= (TIMER | AUDIO | VIDEO | EVENTS | \
                JOYSTICK | HAPTIC | GAMECONTROLLER | SENSORS \
            )
};


enum  IMGInitFlags
{
	JPG=0x00000001,
	PNG=0x00000002,
	TIF=0x00000004,
	WEBP=0x00000008
};

enum  MIXInitFlags
{
	FLAC   = 0x00000001,
    MOD    = 0x00000002,
    MP3    = 0x00000008,
    OGG    = 0x00000010,
    MID    = 0x00000020,
    OPUS   = 0x00000040
};

namespace SDLLoader
{

		bool init(SDLInitFlags SDLflag=SDLInitFlags::EVERYTHING,IMGInitFlags IMGflag=IMGInitFlags::PNG,MIXInitFlags MIXflag=MIXInitFlags::OGG);
		void free();

}

#endif