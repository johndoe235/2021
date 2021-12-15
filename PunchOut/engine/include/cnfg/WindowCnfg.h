#ifndef __JOE_WINDOW_CNFG__
#define __JOE_WINDOW_CNFG__


/* C system includes */

/* C++ system inludes */
#include <cstdint>
#include <string>

/* Third-party includes */

/* Own includes */

/* Forward Declaration */

enum  WindowFlags
{
  /*more information 
    at https://wiki.libsdl.org/SDL_WindowFlags
  */
  FULLSCREEN=0x00000001, //fulscreen window
  FULLSCREN_DESKTOP= ( FULLSCREEN | 0x00001000 ), //fullscreen window at the current desktop resolution
  OPENGL=0x00000002, //window usable with OpenGL context
  VULKAN=0x10000000, //window usable with a Vulkan instance
  SHOWN=0x00000004, //window is visible
  HIDDEN=0x00000008, //window is not visible
  BORDERLESS=0x00000010, //no window decoration
  RESIZEABLE=0x00000020, //window can be resized
  MINIMIZED=0x00000040, //window is minimized
  MAXIMIZED=0x00000080, //window is maximized 
  INPUT_FOCUS=0x00000200, //window has grabbed input focus
  MOUSE_FOCUS=0x00000400, //window has grabbed mouse focus
  FOREIGN=0x00000800, //window was no created by SDL
  HIGHDP=0x00002000, //window should be created in high-DPI mode if supported
  MOUSE_CAPTURE=0x00004000,//window has mouse captured 
  ALWAYS_TOP=0x00008000,//window should always be above others
  SKIP_TASKBAR=0x00010000,//window should not be added to the taskbar
  UTILITY=0x00020000,//window should be treated as a utility window
  TOOLTIP=0x00040000, //window should be treated as a tooltip
  POPUP_MENU=0x00080000 //window should be treated as a popup menu
};

struct WindowCnfg
{

  uint32_t displayMode { 0 };
  uint32_t windowWidth { 0 };
  uint32_t windowHeight { 0 };
  std::string title;

};
#endif