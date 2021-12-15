#include "../../include/fight/Lifebar.h"
#include "../../../engine/include/Renderer.h"

#include <iostream>
Lifebar::Lifebar()
{
    allocate_dest();

}
Lifebar::~Lifebar()
{
    deallocate_dest();
}
void Lifebar::update(int health)
{
    if(amount_to_take==0)
    {
        amount_to_take=(float)getWidth()*0.01f;
        current_visual_health=static_cast<float>(getWidth());

    }

    if(current_health>=health && getWidth()>0)
    {
      
        current_health--;
        current_visual_health-=amount_to_take;
        
        setWidth(static_cast<int>(current_visual_health));
       
        
        
    }
}

void Lifebar::draw()
{
    Fill(255,255,255);
}
