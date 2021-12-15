#ifndef __JOE_RESOURCE_MANAGER__
#define __JOE_RESOURCE_MANAGER__

/* C system includes */

/* C++ system includes */

#include <string>
#include <cstdint>
#include <unordered_map>
/* Third-party includes */

/* Own includes */

/* Forward Declaration */
class Texture;
struct Chunk;
struct Music;
/*                     */ 

class ResourceManager
{
public:
    static  ResourceManager* getInstance();
    

    bool loadTexture(uint32_t index,std::string path);

    bool loadSound(uint32_t index,std::string path); //chunk
    bool loadMusic(uint32_t index,std::string path);
    void pauseMusic();
    void ResumeMusic();
    bool playMusic(uint32_t index,int loops=0);
    
    bool playSound(uint32_t index,int loops=0);
    
    Texture* getTexture(uint32_t key);
    void free();
     
private:
    ResourceManager()=default;
    static ResourceManager* instance;
    std::unordered_map<uint32_t,Texture*> texture_map;
    std::unordered_map<uint32_t,Chunk*> chunk_map;
    std::unordered_map<uint32_t,Music*> music_map;
};

  extern ResourceManager* ResourceMngr;


#endif