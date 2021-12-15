#include "../../include/boxers/lilMac.h"
#include "../../../engine/include/Texture.h"
#include "../../include/timers/lilMacTimers.h"
#include "../../../engine/include/Image.h"
using namespace lilMacTimers;


void lilMac::init()
{
    _name="little mac";
    _win_lose_ko="0-0 0KO";

    positions[BATTLE_POSITION].x=GameObject::getScreenWidth()/2-55;
    positions[BATTLE_POSITION].y=GameObject::getScreenHeight()/2+100;
    positions[INTRO_POSITION].x=positions[BATTLE_POSITION].x;
    positions[INTRO_POSITION].y=positions[BATTLE_POSITION].y+100;
    positions[NEUTRAL_POSITION].x=positions[INTRO_POSITION].x;
    positions[NEUTRAL_POSITION].y=positions[NEUTRAL_POSITION].y;

    setPosition(positions[INTRO_POSITION].x,positions[INTRO_POSITION].y,100,200);

    startsRepresentation.setPosition(110,43,30,30);
    heartsRepresentation.setPosition(185,43,30,30);

    portrait->setPosition(10,350,300,200);
    portrait->setTexture(texture);

    life.setPosition(296,46,160,20);

 
  
  heartsRepresentation.write("00");
  startsRepresentation.write("0");
  punch_information={false,false,0,0,false};

  loadFrames();
 }
void lilMac::dodgeLeft()
{
    dodge();
}
void lilMac::dodgeRight()
{
    if(!_isLocked)
    setTextureFlip_HORIZONTAL();
    dodge();
}
void lilMac::bodyShotLeft()
{
    bodyShot();
}
void lilMac::bodyShotRight()
{
    if(!_isLocked)
     setTextureFlip_HORIZONTAL();

    bodyShot();
}
void lilMac::headShotLeft()
{
    headShot();
}
void lilMac::headShotRight()
{
    if(!_isLocked)
     setTextureFlip_HORIZONTAL();

    headShot();
}
void lilMac::superShot()
{
    if(!_isLocked)
    {
        action.reset(new superShotTimer(this));
        action->onStart();
    
    }
}
void lilMac::loadFrames()
{
    
    int32_t w=40,h=81; //size of one animation sprite 40 81
    insert_AnimationFrame(6,5,w,h);//PASSIVE_ZERO
    insert_AnimationFrame(43,5,w,h);//PASSIVE_ONE

    insert_AnimationFrame(5,76,w,h); //DODGE_ZERO
    insert_AnimationFrame(39,76,w,h);//DODGE_ONE
    insert_AnimationFrame(79,76,w,h);//DODGE_TWO

    insert_AnimationFrame(6,147,w,h); //BLOCK_ZERO
    insert_AnimationFrame(40,147,w,h); //BLOCK_ONE
    insert_AnimationFrame(90,149,w,h);//BLOCK TWO

    insert_AnimationFrame(11,230,w,h); //BODY_SHOT_ZERO
    insert_AnimationFrame(49,230,w,h);//BODY_SHOT_ONE
    insert_AnimationFrame(80,229,w,h);//BODY_SHOT_TWO

    insert_AnimationFrame(10,322,w,h);//UP_PUNCH_ZERO
    insert_AnimationFrame(41,320,w,h);//UP_PUNCH_ONE
    insert_AnimationFrame(76,310,w,h);//UP_PUNCH_TWO

    insert_AnimationFrame(5,411,w,h);//SUPER_PUNCH_ZERO
    insert_AnimationFrame(38,411,w,h);//SUPER_PUNCH_ONE
    insert_AnimationFrame(77,411,w,h);//SUPER_PUNCH_TWO
    insert_AnimationFrame(110,404,w,h); //SUPER_PUNCH_THREE
    insert_AnimationFrame(149,402,w,h);//SUPER_PUNCH_FOUR
    insert_AnimationFrame(188,402,w,h);//SUPER_PUNCH_FIVE

    insert_AnimationFrame(5,481,w,h); ///TIRED_ZERO
    insert_AnimationFrame(39,482,w,h);//TIRED_ONE

    insert_AnimationFrame(7,559,w,h); //PUNCHED_ZERO
    insert_AnimationFrame(45,559,w,h);//PUNCHED_ONE
    insert_AnimationFrame(88,548,w,h);//KO_D

    insert_AnimationFrame(5,641,w,h); //VICTORY_ZERO
    insert_AnimationFrame(39,641,w,h);///VICTORY_ONE

    insert_AnimationFrame(9,873,80,69);//PORTRAIT_GREAT_ZERO
    insert_AnimationFrame(92,873,80,69);//PORTRAIT_GREAT_ONE
    insert_AnimationFrame(175,873,80,69);//PORTRAIT_GREAT_TWO
    insert_AnimationFrame(258,873,80,69);//PORTRAIT_GREAT_THREE



    CURRENT_FRAME=LIL_MAC_FRAMES::PASSIVE_ONE;
    changeFrame(CURRENT_FRAME);
    changePortraitSource(static_cast<uint32_t>(LIL_MAC_FRAMES::PORTRAIT_GREAT_THREE));
    
    
}

void lilMac::changeFrame(LIL_MAC_FRAMES frame_name)
 {
     CURRENT_FRAME=frame_name;
     changeSource(static_cast<int32_t>(frame_name));
 }
void lilMac::changePortraitFrame(LIL_MAC_FRAMES portrait_name)
{
    CURRENT_FRAME=portrait_name;
   changePortraitSource(static_cast<int32_t>(portrait_name));
}
 LIL_MAC_FRAMES lilMac::getFrameName()
 {
     return CURRENT_FRAME;
 }
 
 /*
bool lilMac::isTextureFlipped()
{
      return flipFrame;
}

void lilMac::setTextureFlip_NONE()
{
    flipFrame=false;
}
*/


void lilMac::dodge()
{
    if(!_isLocked)
    {
        action.reset(new dodgeTimer(this));
        action->onStart();
    }
}
void lilMac::bodyShot()
{
    if(!_isLocked && !_isPlayerTired)
    {
        action.reset(new bodyShotTimer(this));
        action->onStart();
    }
}
void lilMac::headShot()
{
    if(!_isLocked && !_isPlayerTired)
    {
        action.reset(new headShotTimer(this));
        action->onStart();
    }
}
void lilMac::block()
{
    if(!_isLocked && !_isPlayerTired)
    {
       
        if(action !=nullptr && action->id==static_cast<uint32_t>(MAC_TIMER_ID::CAN_DODGE_AFTER_BLOCK_TIMER))
        {
            action.reset(new dodgeAfterBlockTimer(this));
            action->onStart();
           
        }
        else
        {
            action.reset(new blockTimer(this));
            action->onStart();
        }
        
    }
}
void lilMac::unblock()
{
    if(action !=nullptr && action->id==static_cast<uint32_t>(MAC_TIMER_ID::BLOCK_TIMER))
    {
        changeFrame(LIL_MAC_FRAMES::PASSIVE_ONE);
        action.reset(new canDodgeAfterBlockTimer());
        action->onStart();
    }
    
} 

void lilMac::update()
{
    if(action!=nullptr)
    {
    if(action->isActive())
    {
        action->onActive();
    }
    if(action->isExpired())
    {
        if(action->shouldActionReset())
        {
            action->onExpire();
            action.reset();
            
        }
        else
        action->onExpire();
    }
    }
    
    if(specialTimer!=nullptr && action==nullptr)
    {
       
         if(specialTimer->isActive())
        {
            specialTimer->onActive();
        }
        if(specialTimer->isExpired())
        {
            specialTimer->onExpire();
            setSpecialAction(MAC_TIMER_ID::DEFAULT_TIMER);
            
        }
    }
    life.update(hp);
    
}

 void lilMac::updatePortrait()
 {
     if(action==nullptr || action->id!=static_cast<uint32_t>(MAC_TIMER_ID::PORTRAIT_TIMER))
     {
        setAction(MAC_TIMER_ID::PORTRAIT_TIMER);
        
       
     }
     update();
     
 }
bool lilMac::handleIncomingPunch(Punch& punch)
{
    if(_isVulnerable)
    {
        hp-=punch.damage;
        decreaseHearts(3);
        heartsRepresentation.write(std::to_string(hearts));
        action.reset(new punchedTimer(this));
        action->onStart();

        
        return true;
    }

    return false;
}
 void lilMac::setAction(MAC_TIMER_ID id)
 {
        switch(id)
    {
        case MAC_TIMER_ID::KO_DTIMER:
        action.reset(new KO_dTimer(this));
        break;
        case MAC_TIMER_ID::MOVE_TO_NEUTRAL_POSITION_TIMER:
        action.reset(new walkToNeutralPosition(this,positions[NEUTRAL_POSITION].x,positions[NEUTRAL_POSITION].y));
        break;
        case MAC_TIMER_ID::MOVE_TO_BATTLE_POSITION_TIMER:
        action.reset(new walkToBattlePosition(this,positions[BATTLE_POSITION].x,positions[BATTLE_POSITION].y));
        break;
        case MAC_TIMER_ID::CHEER_TIMER:
        action.reset(new cheerTimer(this));
        break;
        case MAC_TIMER_ID::PORTRAIT_TIMER:
        action.reset(new portraitAnimationTimer(this));
        default:
        break;
    }
    action->onStart();
 }
 void lilMac::setMaxHearts(int32_t Hearts)
 {
     max_hearts=Hearts;
     hearts=max_hearts;
     heartsRepresentation.write(std::to_string(hearts));
 }

void lilMac::draw()
{
    life.draw();
    heartsRepresentation.draw();
    startsRepresentation.draw();

    GameObject::draw();
}
 void lilMac::decreaseHearts(int32_t amount)
 {
     if(hearts-amount>=0)
        hearts-=amount;
     else
        hearts=0;

    heartsRepresentation.write(std::to_string(hearts));
    if(hearts==0)
    {
    _isPlayerTired=true;
    setSpecialAction(MAC_TIMER_ID::TIRED_TIMER);
    }
 }

 void lilMac::setSpecialAction(MAC_TIMER_ID id)
 {
     switch(id)
     {
         case MAC_TIMER_ID::TIRED_TIMER:
         specialTimer.reset(new tiredTimer(this));
         break;
         case MAC_TIMER_ID::DEFAULT_TIMER:
         specialTimer.reset(new defaultTimer(this));
         break;
         default:
         break;
     }
     specialTimer->onStart();
 }
 void lilMac::rested()
 {
     hearts=max_hearts;
     _isPlayerTired=false;
     heartsRepresentation.write(std::to_string(hearts));
 }

void  lilMac::cheer()
{   
    
     if(action != nullptr && action->id!=static_cast<uint32_t>(MAC_TIMER_ID::CHEER_TIMER))
    setAction(MAC_TIMER_ID::CHEER_TIMER);
    else if(action==nullptr)
    setAction(MAC_TIMER_ID::CHEER_TIMER);
}
void  lilMac::IntroAnimation()
{
    ///lilMac doesn't have one
}
bool  lilMac::isInNeutralPosition()
{
    return (getXposition()==positions[NEUTRAL_POSITION].x && getYposition()==positions[NEUTRAL_POSITION].y);
}

void  lilMac::moveToNeutralPosition()
{
    setAction(MAC_TIMER_ID::MOVE_TO_NEUTRAL_POSITION_TIMER);
    
}
void  lilMac::moveToBattlePosition()
{
    setAction(MAC_TIMER_ID::MOVE_TO_BATTLE_POSITION_TIMER);
    makeVulnerable();
    Unlock();
}