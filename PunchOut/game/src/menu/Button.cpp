#include "../../include/menu/Button.h"

Button::Button(Button_ID ID)
:id(ID)
{
    
    allocate_dest();
   // allocate_texture();

    locked=false;
    visible=true;
}
Button::~Button()
{
    
    deallocate_dest();
   // deallocate_texture();
}
bool Button::isClicked()
{
    return _clicked;
}
bool Button::isSelected()
{
    return _selected;
}