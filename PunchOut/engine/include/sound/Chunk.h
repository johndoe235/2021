#include "SDL_mixer.h"
#ifndef __JOE_CHUNK__
#define __JOE_CHUNK__

struct Chunk
{
    public:
    void free()
    {
        if(chunk!=0)
        {
            Mix_FreeChunk(chunk);
            chunk=0;
        }
    }
    Mix_Chunk* chunk=0;
};

struct Music
{
    void free()
    {
        if(music!=0)
        {
        Mix_FreeMusic(music);
        music=0;
        }
    }
    Mix_Music* music=0;
};
#endif
