#include "../include/Texture.h"
#include <SDL_image.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <iostream>
#include "../../engine/include/managers/ResourceManager.h"
Texture::Texture()
:pTexture(nullptr)
{

}
Texture::~Texture()
{
    free();
}
Texture::Texture(Renderer*& renderer,std::string path)
{
    createTexture(renderer,path);
}


void Texture::free()
{
    if(!pTexture)
        SDL_DestroyTexture(pTexture);
}

bool Texture::createTexture(Renderer*& renderer,std::string path)
{
    SDL_Surface* temp=IMG_Load(path.c_str());

    if(!temp) //==nullptr
    {
        std::cerr<<"Cannot load SDL_Surface from "<<path<<"\nError:"<<IMG_GetError()<<"\n";
        return false;
    }

    pTexture=SDL_CreateTextureFromSurface(renderer->pRenderer,temp);

    if(!pTexture) //==nullptr
    {
        std::cerr<<"Cannot create Texture from SDL_Surface! "<<IMG_GetError()<<"\n";
        return false;
    }
    SDL_FreeSurface(temp);
    
    return true;
}
 bool Texture::createTextureFromSurface(Renderer*& renderer,SDL_Surface*& temp)
 {
     if(!temp) //==nullptr
    {
        std::cerr<<"Cannot load SDL_Surface"<<"\nError:"<<IMG_GetError()<<"\n";
        return false;
    }

    pTexture=SDL_CreateTextureFromSurface(renderer->pRenderer,temp);

    if(!pTexture) //==nullptr
    {
        std::cerr<<"Cannot create Texture from SDL_Surface! "<<IMG_GetError()<<"\n";
        return false;
    }
    
    return true;
 }
void Texture::setAlphaMod(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(pTexture,alpha);
}
void Texture::setBlendMode(RendererBlendMode mode)
{
        SDL_SetTextureBlendMode(pTexture,static_cast<SDL_BlendMode>(mode));
}
void Texture::setTextureColorMode(uint8_t r,uint8_t g,uint8_t b)
{
    SDL_SetTextureColorMod(pTexture,r,g,b);
}
/*
 SDL_Texture*& Texture::getRawTexture()
 {
     
     return pTexture;
 }
 */



