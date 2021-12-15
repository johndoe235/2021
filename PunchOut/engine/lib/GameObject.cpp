#include "../include/GameObject.h"
#include "../../engine/include/Texture.h"
#include "../../engine/include/Renderer.h"
#include "SDL_rect.h"
#include <iostream>
#include "../../engine/include/managers/DrawManager.h"
#include "../../engine/include/managers/ResourceManager.h"
#include "../../engine/include/Renderer.h"

GameObject::~GameObject()
{
    if(_hasSourceAllocated)
        deallocate_source();

    if(_hasTextureAllocated)
        deallocate_texture();
  
}
void GameObject::moveUp(int32_t x)
{
    dest->y-=x;
}
void GameObject::moveDown(int32_t x)
{
    dest->y+=x;
}

void GameObject::moveLeft(int32_t x)
{
    dest->x-=x;
}
void GameObject::moveRight(int32_t x)
{
    dest->x+=x;
}
void GameObject::rotate(double degrees)
{
    angle=degrees;
}
void GameObject::setPosition(int x,int y,int w,int h)
{
    if(dest==0)
        allocate_dest();


    if(dest)
    {
        dest->x=x;
        dest->y=y;
        dest->w=w;
        dest->h=h;
    }
    
    
}
void GameObject::setSourcePosition(int x,int y,int w,int h)
{
    if(source==0)
        allocate_source();

    if(source)
    {
        source->x=x;
        source->y=y;
        source->w=w;
        source->h=h;
    }
    else
    {
        std::cerr<<"GameObject ERROR: Trying to access unallocated memory\n Function:setSourcePosition(int x,int y,int w,int h)\n";
    }
}

void GameObject::setSourcePositionRaw(SDL_Rect* Source)
{
    setSourcePosition(Source->x,Source->y,Source->w,Source->h);
}
void GameObject::draw()
{
    unoverridable_draw();
}

void GameObject::unoverridable_draw()
{
    if(texture==0)
    std::cerr<<"Fatal crash Texture was null!\n";
    else
    DrawMngr->renderer->drawEx(texture,source,dest,angle,center,flip);
}
/*
bool GameObject::loadTexture(std::string path,Renderer*& renderer)
{
    if(texture->createTexture(renderer,path))
    return true;

    return false;
}
*/
void GameObject::setTextureFlip_NONE()
{
    flip=RendererFlip::FLIP_NONE;
}
void GameObject::setTextureFlip_HORIZONTAL()
{
    flip=RendererFlip::FLIP_HORIZONTAL;
}
void GameObject::setTextureFlip_VERTICAL()
{
    flip=RendererFlip::FLIP_VERTICAL;
}

bool GameObject::isTextureFlipped()
{
    if(flip==RendererFlip::FLIP_NONE)
    return false;
    else
    return true;
}

bool GameObject::isTextureFlipped_HORIZONTAL()
{
    if(flip==RendererFlip::FLIP_HORIZONTAL)
    return true;
    else
    return false;
}
bool GameObject::isTextureFlipped_VERTICAL()
{
    if(flip==RendererFlip::FLIP_VERTICAL)
        return true;
    else
        return false;
}
int GameObject::getWidth()
{
    if(dest!=0)
    return dest->w;

    return 0;
}

int GameObject::getHeight()
{
    if(dest!=0)
    return dest->h;

    return 0;
}
int GameObject::getXposition()
{
    if(dest!=0)
    return dest->x;
    
    return 0;
}
int GameObject::getYposition()
{
    if(dest!=0)
    return dest->y;

    return 0;
}

void GameObject::setWidth(int amount)
{
    if(dest==0)
    allocate_dest();

    if(dest!=0)
    dest->w=amount;
     else
        std::cerr<<"GameObject ERROR: Trying to access unallocated memory\n Function:setWidth(int amount)\n";

}
void GameObject::setHeight(int amount)
{
    if(dest==0)
        allocate_dest();

    if(dest!=0)
    dest->h=amount;
    else
        std::cerr<<"GameObject ERROR: Trying to access unallocated memory\n Function:setHeight(int amount)\n";
}
void GameObject::setXposition(int amount)
{
       if(dest==0)
        allocate_dest();

    if(dest!=0)
    dest->x=amount;
    else
        std::cerr<<"GameObject ERROR: Trying to access unallocated memory\n Function:setXposition(int amount)\n";
}
void GameObject::setYposition(int amount)
{
    if(dest==0)
        allocate_dest();

    if(dest!=0)
    dest->y=amount;
    else
        std::cerr<<"GameObject ERROR: Trying to access unallocated memory\n Function:setYposition(int amount)\n";
}

void GameObject::allocate_center()
{
    
    if(!center)
    deallocate_center();
    
    center=new SDL_Point{};
    _hasCenterAllocated=true;
}
void GameObject::allocate_source()
{
    if(!source)
    deallocate_source();

    source=new SDL_Rect{};
    _hasSourceAllocated=true;
}
void GameObject::allocate_dest()
{
    if(!dest)
    deallocate_dest();

    dest=new SDL_Rect{};
    _hasDestAllocated=true;
}
void GameObject::allocate_texture()
{
    if(!texture)
    deallocate_texture();

    texture=new Texture{};
    _hasTextureAllocated=true;
}


void GameObject::deallocate_center()
{
     
    if(!center)
    {
     delete center;
     center=0;
     _hasCenterAllocated=false;
    }
}
void GameObject::deallocate_source()
{
    if(!source)
    {
        delete source;
        source=0;
        _hasSourceAllocated=false;
    }
}
void GameObject::deallocate_dest()
{
    if(!dest)
    {
        delete dest;
        dest=0;
        _hasDestAllocated=false;
    }
}
void GameObject::deallocate_texture()
{
    if(!texture)
    {
    delete texture;
    texture=0;
    _hasTextureAllocated=false;
    }
}
 bool GameObject::loadTexture(uint32_t index,std::string path)
{
    return ResourceMngr->loadTexture(index,path);
}
 Texture* GameObject::getTexture(uint32_t texture_index)
{
    return ResourceMngr->getTexture(texture_index);
}
int32_t GameObject::getScreenWidth()
{
    return DrawMngr->WindowWidth();
}
int32_t GameObject::getScreenHeight()
{
    return DrawMngr->WindowHeight();
}
void GameObject::setTexture(uint32_t textureName)
{
    texture=getTexture(textureName);
}
void GameObject::setTexture(Texture* Texture)
{
    texture=Texture;
}
void GameObject::Fill(uint8_t r,uint8_t g,uint8_t b)
{
     DrawMngr->renderer->changeRGB(r,g,b);
    DrawMngr->renderer->FillRectangle(dest);
    DrawMngr->renderer->changeRGB(0,0,0);
}
void GameObject::changeTextureColorMod(uint8_t r,uint8_t g,uint8_t b)
{
    if(texture!=0)
    {
        texture->setTextureColorMode(r,g,b);
    }
}
bool GameObject::loadMusic(uint32_t index,std::string path)
{
   return ResourceMngr->loadMusic(index,path);
}
bool GameObject::loadSound(uint32_t index,std::string path)
{
    return ResourceMngr->loadSound(index,path);
}
bool GameObject::playMusic(uint32_t index,int loops)
{
    return ResourceMngr->playMusic(index,loops);
}
bool GameObject::playSound(uint32_t index,int loops)
{
    return ResourceMngr->playSound(index,loops);
}
void GameObject::pauseMusic()
{
   ResourceMngr->pauseMusic();
}
void GameObject::resumeMusic()
{
 ResourceMngr->ResumeMusic();
}
