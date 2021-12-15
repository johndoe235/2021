#include "../../include/managers/DrawManager.h"
#include "../../include/Renderer.h"
#include "../../include/Window.h"

DrawManager* DrawManager::instance=nullptr;
DrawManager* DrawMngr =nullptr;

DrawManager* DrawManager::getInstance()
 {
     if(instance==nullptr)
     {
         instance=new DrawManager();
         instance->window=new Window();
         instance->renderer=new Renderer();
     }

     return instance;
 }


void DrawManager::free()
{
      if(renderer!=nullptr)
    {
        renderer->free();
        delete renderer;
        renderer=0;
    }
    
    if(window!=nullptr)
    {
        window->free();
        delete window;
        window=0;
    }
    if(instance!=nullptr)
    {
    delete instance;
    instance=nullptr;
    }
  

}
 bool DrawManager::init(WindowCnfg& cnfg)
 {
     if(!window->init(cnfg))
     return false;

     if(!renderer->init(*window))
     return false;

    return true;
 }

int32_t DrawManager::WindowWidth()
{
    return DrawMngr->window->getWidth();
}
int32_t DrawManager::WindowHeight()
{
    return DrawMngr->window->getHeight();
}
