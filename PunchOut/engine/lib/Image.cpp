#include "../include/Image.h"

void Image::makeInvisible()
{
    _isVisible=false;
}
void Image::makeVisible()
{
    _isVisible=true;
}
void Image::draw()
{
    if(_isVisible)
        GameObject::draw();
}
