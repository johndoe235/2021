#ifndef __JOE_RENDERER_ENUMS__
#define __JOE_RENDERER_ENUMS__

enum RendererFlip
{
	FLIP_NONE=0,
	FLIP_HORIZONTAL,
	FLIP_VERTICAL
};
enum class RendererFlags
{
	/*more information 
 		at https://wiki.libsdl.org/SDL_RendererFlags
	*/
	SOFTWARE=0x00000001,
	ACCELERATED=0x00000002,
	VSYNC=0x00000004,
	TARGET_TEXTURE=0x00000008
};

enum RendererBlendMode
{
	BlendModeNone=0,
	BlendModeBlend,
	BlendModeAdd,
	BlendModeMod
};


#endif