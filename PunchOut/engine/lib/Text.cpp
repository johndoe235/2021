#include "../include/Text.h"
#include "../include/Texture.h"
#include "../include/managers/DrawManager.h"
#include "../include/utils/Font.h"
#include <iostream>

FontContainer* Text::fontContainer=0;
std::unordered_map<char,Texture*> Text::characters=std::unordered_map<char,Texture*>();



void Text::loadEngineFont(std::string path,int FontSize)
{
    if(fontContainer==nullptr)
    {
        fontContainer=new FontContainer();
        fontContainer->_font=TTF_OpenFont(path.c_str(),FontSize);

        if(fontContainer->_font==nullptr)
        {
            std::cerr<<"Cannot load Font! "<< TTF_GetError()<<"\n";
            delete fontContainer;
            return;
        }

       std::string ALL_CHARACTERS=" !?.0123456789:ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-\"\'";
       SDL_Surface* text;
       char* symbol=new char[2]{'0','\0'};
       //symbol[1]='\0';
        for(char var:ALL_CHARACTERS)
        {
           symbol[0]=var;

            text=TTF_RenderText_Solid(fontContainer->_font,symbol,{255,255,255,255});
        
            if(text!=nullptr)
            {
                Texture* p=new Texture();
                p->createTextureFromSurface(DrawMngr->renderer,text);
                characters.emplace(std::make_pair(var,p));
            
            }
            SDL_FreeSurface(text);
        }
        delete[] symbol;
       
    }
    else
    std::cerr<<"Font Pointer points to allocated memory\n";
}
void Text::freeEngineFont()
{
    if(fontContainer!=nullptr)
    {
        TTF_CloseFont(fontContainer->_font);

        fontContainer->_font=nullptr;
        delete fontContainer;
        fontContainer=nullptr;
    

    for(auto itt=characters.begin();itt!=characters.end();itt++)
    {
        delete itt->second;
    }   
    }
}

void Text::draw()
{
    int x=getXposition();
    int y=getYposition();
    for(auto& symbol:_text)
    {
       
        if(symbol!='\n')
        {
        texture=getLetter(symbol);
        GameObject::draw();
        setXposition(getXposition()+ getWidth());
        }
        else
        {
        setYposition(getYposition()+getHeight());
        setXposition(x);
        }
    }
    setXposition(x);
    setYposition(y);
}
void Text::write(std::string string)
{
    _text=string;
}
Texture* Text::getLetter(char letter)
{
    auto itt=characters.find(letter);
    if(itt!=characters.end())
    return itt->second;
    else
    return 0;

}