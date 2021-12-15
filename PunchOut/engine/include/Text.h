#ifndef __JOE_TEXT__
#define __JOE_TEXT__


/* C system includes */

/* C++ system includes */
#include <string>
#include <memory>
#include <unordered_map>
/* Third-party includes */

/* Own includes */
#include "GameObject.h"
/* Forward Declaration */
struct  FontContainer;
/*                    */







class Text :public GameObject
{
    public:
        
        static void  loadEngineFont(std::string path,int fontSize);
        static void  freeEngineFont();
       
        void draw() override;
        void write(std::string string);
    
    protected:
    static FontContainer* fontContainer;
    static std::unordered_map<char,Texture*> characters;
    Texture* getLetter(char letter);
    

    std::string _text;
};
#endif