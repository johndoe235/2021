#include "../../include/menu/Menu.h"
#include "../../include/menu/Button.h"
#include "../../include/Resources.h"
#include <iostream>
Menu::Menu()
:_select(Button_ID::NONE)
{
   /// allocate_dest();
   // allocate_texture();

    selectedB_index=-1;
    buttons.push_back(Button(Button_ID::NEW_GAME));
    buttons.push_back(Button(Button_ID::CONTINUE));
    selectedB_index=0;
}
Menu::~Menu()
{
   // deallocate_dest();
   // deallocate_texture();
}
void Menu::clickSelectedButton()
{
    buttonClickedID=buttons[selectedB_index].id;
}
void Menu::load()
{
    
    setTexture(PUNCH_OUT_TEXTURES::MENU_TITLE_SCREEN);
    buttons[0].setTexture(PUNCH_OUT_TEXTURES::MENU_NEW_GAME);
    buttons[1].setTexture(PUNCH_OUT_TEXTURES::MENU_CONTINUE);
    _select.setTexture(PUNCH_OUT_TEXTURES::MENU_GLOVE);
    


    int x=270,y=350,w=295,h=60;
    buttons[0].setPosition(x,y,w,h);
    buttons[1].setPosition(x,y+65,w,h);
    _select.setPosition(x-70,y,70,60);



}
void Menu::nextButton()
{
    
    if(selectedB_index==-1)
    return;

    if(selectedB_index<static_cast<int>(buttons.size()-1) )
    {
        
        selectedB_index++;
    }
    else
        selectedB_index=0;

    
   _select.setXposition(buttons[selectedB_index].getXposition()- _select.getWidth());
   _select.setYposition(buttons[selectedB_index].getYposition());
    

}

void Menu::previousButton()
{
    if(selectedB_index==-1)
    return;

    if(selectedB_index-1>=0)
        selectedB_index--;
    else
        selectedB_index=static_cast<int>(buttons.size()-1);

    
    _select.setXposition(buttons[selectedB_index].getXposition()-_select.getWidth());
    _select.setYposition(buttons[selectedB_index].getYposition());
}
void Menu::draw()
{
    GameObject::draw();

    for(auto& button:buttons)
        button.draw();

    
    _select.draw(); //LEFT SIDE GLOVE

    // moveGlove();
    
    
    
    
    

}
void Menu::moveGlove()
{
    
    if(_select.getXposition()<buttons[selectedB_index].getXposition())
    {
        _select.setXposition(buttons[selectedB_index].getXposition() + buttons[selectedB_index].getWidth());
    }
    else
    {
        _select.setXposition(buttons[selectedB_index].getXposition()-_select.getWidth());
    }
}


Button_ID Menu::clickedButton()
{   
    if(buttonClickedID!=Button_ID::NONE)
    {
        Button_ID temp=buttonClickedID;
        buttonClickedID=Button_ID::NONE;
        return temp;
    }
    else
    return Button_ID::NONE;
}
