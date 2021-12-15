#include "../../include/fight/PointSystem.h"
PointSystem::PointSystem()
{
    addPoint(0);
}
void PointSystem::draw()
 {
     int32_t default_position=getXposition();
     int32_t normalized_position=static_cast<int32_t>(getXposition()- getWidth()*(_text.length()-1));
     setXposition(normalized_position);
     for(auto& symbol:_text)
    {
        texture=getLetter(symbol);
        GameObject::draw();
        setXposition(getXposition()+ getWidth());
    }
    setXposition(default_position);
 }
void PointSystem::addPoint(int32_t point)
{
    points+=point;    
    _text=std::to_string(points);

}
std::string PointSystem::getPoints_to_string()
{
    return _text;
}
int32_t PointSystem::getPoints()
{
    return points;
}