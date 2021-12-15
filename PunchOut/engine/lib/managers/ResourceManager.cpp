#include "../../include/managers/ResourceManager.h"
#include "../../include/managers/DrawManager.h"
#include "../../include/Texture.h"
#include "../../include/sound/Chunk.h"
#include <iostream>

ResourceManager* ResourceManager::instance=nullptr;
ResourceManager* ResourceMngr=nullptr;

ResourceManager*  ResourceManager::getInstance()
{
    if(instance==nullptr)
     {
         instance=new ResourceManager();   
       
     }

     return instance;
}
bool ResourceManager::loadTexture(uint32_t index,std::string path)
{
   
    Texture* temp=new Texture();
    
    if(temp->createTexture(DrawMngr->renderer,path))
    {
    texture_map.insert(std::make_pair(index,temp));
    return true;
    }
    else
    {
        delete temp;
        return false;
    }


}
Texture* ResourceManager::getTexture(uint32_t key)
{
    auto itt=texture_map.find(key);

    if(itt!=texture_map.end())
    return itt->second;
    else
    return 0;
}

void ResourceManager::free()
{
    
    for(auto itt=texture_map.begin();itt!=texture_map.end();itt++)
    {
        if(itt->second!=nullptr)
        {
            itt->second->free();
            delete itt->second;
            itt->second=nullptr;
        }
    }

     for(auto itt=chunk_map.begin();itt!=chunk_map.end();itt++)
    {
        if(itt->second!=nullptr)
        {
            itt->second->free();
            delete itt->second;
            itt->second=nullptr;
        }
    }

     for(auto itt=music_map.begin();itt!=music_map.end();itt++)
    {
        if(itt->second!=nullptr)
        {
            itt->second->free();
            delete itt->second;
            itt->second=nullptr;
        }
    }
    
    if(instance!=nullptr)
    {
        delete instance;
        instance=nullptr;
    }
}

bool ResourceManager::playMusic(uint32_t index,int loops)
{
    auto itt=music_map.find(index);

    if(itt!=music_map.end())
    {
        if(Mix_PlayingMusic())
            Mix_PauseMusic();
        

        Mix_PlayMusic(itt->second->music,loops);
        return true;
    }
    
    

    std::cerr<<"No such music file found!\n";
    return false;
    


  
}
bool ResourceManager::playSound(uint32_t index,int loops)
{
auto itt=chunk_map.find(index);

    if(itt!=chunk_map.end())
    {
        Mix_PlayChannel(-1,itt->second->chunk,loops);
        return true;
    }
    
    

    std::cerr<<"No such sound/chunk file found!\n";
    return false;

}

bool ResourceManager::loadSound(uint32_t index,std::string path)
{
    Chunk* temp=new Chunk();
    temp->chunk=Mix_LoadWAV(path.c_str());

    if(!temp->chunk)
    {
    std::cerr<<"Cannot load Chunk! "<<Mix_GetError()<<std::endl;
    delete temp;
    return false;
    }

    chunk_map.insert(std::make_pair(index,temp));
    return true;
}
bool ResourceManager::loadMusic(uint32_t index,std::string path)
{
     Music* temp=new Music();
    temp->music=Mix_LoadMUS(path.c_str());

    if(!temp->music)
    {
    std::cerr<<"Cannot load Music! "<<Mix_GetError()<<std::endl;
    delete temp;
    return false;
    }

    music_map.insert(std::make_pair(index,temp));
    return true;

}
void ResourceManager::pauseMusic()
{
    Mix_PauseMusic();
}
void ResourceManager::ResumeMusic()
{
    Mix_ResumeMusic();
}
