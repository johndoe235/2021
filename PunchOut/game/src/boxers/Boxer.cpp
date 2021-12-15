#include "../../include/boxers/Boxer.h"
#include "../../../engine/include/Texture.h"
#include "../../../engine/include/Image.h"
#include "SDL_rect.h"

bool Boxer::_isPlayerTired=false;

Boxer::Boxer()
{
    portrait=new Image();
}
Boxer::~Boxer()
{
    if(!portrait)
    {
    delete portrait;
    portrait=nullptr;
    }
}
std::string Boxer::boxerName()
{
    return _name;
}
std::string Boxer::win_lose_ko_()
{
    return _win_lose_ko;
}
void Boxer::updatePortrait()
{

}

bool Boxer::hasPunchLanded()
{
    if(_doesPunchLand)
    {
        _doesPunchLand=false;
        return true;
    }
    else
    return false;
}

void  Boxer::punchIsLanding()
{
     _doesPunchLand=true;
}
void Boxer::punchNOTLanding()
{
    _doesPunchLand=false;
}

void Boxer::makeVulnerable()
{
    _isVulnerable=true;
}
void Boxer::makeInvulnerable()
{
    _isVulnerable=false;
}
Punch& Boxer::punchInformation()
{
        return punch_information;
}
void Boxer::setPunchInfo(bool right,bool high,int dmg,int points)
{
    punch_information.right_side_punch=right;
    punch_information.high_punch=high;
    punch_information.damage=dmg;
    punch_information.points=points;
}

void  Boxer::insert_AnimationFrame(int x,int y,int w,int h)
{
    sources.emplace_back(SDL_Rect{x,y,w,h});
}
 

void Boxer::changeSource(int32_t index)
{
    if(index<static_cast<int32_t>(sources.size()))
    {
        source=&sources[index];
    }
}
void Boxer::changePortraitSource(int32_t index)
{
    if(index<static_cast<int32_t>(sources.size()))
    {
        portrait->setSourcePositionRaw(&sources[index]);
    }
}
int32_t Boxer::getHP()
{
    return hp;
}
void Boxer::Lock()
 {
     _isLocked=true;

 }
 void Boxer::Unlock()
 {
     _isLocked=false;
 }
 bool  Boxer::isKO_D()
 {
     return _Ko_d;
 }
 bool Boxer::stoodUp()
 {
     return _stoodUp;
 }
 void Boxer::KO()
 {
     _Ko_d=true;
 }
void  Boxer::draw()
{
    life.draw();
    GameObject::draw();
}

void Boxer::drawPortrait()
{
    portrait->draw();
}
bool Boxer::isPlayerTired()
{
return _isPlayerTired;
}
bool Boxer::hasIntroEnded()
{
    return _hasIntroEnded;
}
/*
void Boxer::IntroAnimation()
{
    
}
bool Boxer::isInNeutralPosition()
{

}
void Boxer::introPosition()
{

}
void Boxer::neutralPosition()
{

}
void Boxer::battlePosition()
{

}
*/
bool Boxer::hasCheerEnded()
{
    return _hasCheerEnded;
}
void Boxer::activateBattleMode()
{
    _battleMode=true;
}
void Boxer::endIntro()
{
    _hasIntroEnded=true;
}
void Boxer::endCheer()
{
    _hasCheerEnded=true;
}
void Boxer::teleportTO_introPosition()
{
    setXposition(positions[INTRO_POSITION].x);
    setYposition(positions[INTRO_POSITION].y);
}
void Boxer::teleportTO_neutralPosition()
{
    setXposition(positions[NEUTRAL_POSITION].x);
    setYposition(positions[NEUTRAL_POSITION].y);
}
void Boxer::teleportTO_battlePosition()
{
    setXposition(positions[BATTLE_POSITION].x);
    setYposition(positions[BATTLE_POSITION].y);
}


 
 