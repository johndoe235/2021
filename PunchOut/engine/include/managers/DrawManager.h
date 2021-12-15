#ifndef __JOE_DRAW_MANAGER__
#define __JOE_DRAW_MANAGER__

/* C system includes */

/* C++ system includes */


/* Third-party includes */

/* Own includes */
#include "../cnfg/WindowCnfg.h"
/* Forward Declaration */
class Window;
class Renderer;
/*                     */ 

class DrawManager
{
public:
    static  DrawManager* getInstance();
    
    bool init(WindowCnfg& cnfg);
    void free();

    int32_t WindowWidth();
    int32_t WindowHeight();
    
    Renderer* renderer;
    Window* window;
private:
    DrawManager()=default;
    static DrawManager* instance;

    
  
};

  extern DrawManager* DrawMngr;



#endif