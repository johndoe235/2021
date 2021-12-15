#include "../../include/boxers/glassJoe.h"
#include "../../../engine/include/Texture.h"
#include "../../include/timers/glassJoeTimers.h"
#include "../../include/Resources.h"
#include "../../../engine/include/Timer.h"
#include "../../../engine/include/Image.h"
#include <iostream>

using namespace glassJoeTimers;

///TESTING FUNCTIONS 




void glassJoe::init()
{
    _name="glass joe";
    _win_lose_ko="1-99 1KO";

  _isVulnerable=false;
  punch_information={false,false,0,0,false};

  positions[INTRO_POSITION].x=GameObject::getScreenWidth()/2+220;
  positions[INTRO_POSITION].y=GameObject::getScreenHeight()/2-300;
  positions[NEUTRAL_POSITION].x=385;
  positions[NEUTRAL_POSITION].y=120;
  positions[BATTLE_POSITION].x=385;
  positions[BATTLE_POSITION].y=220;

  life.setPosition(484,46,160,20);
  setPosition(positions[INTRO_POSITION].x, positions[INTRO_POSITION].y,150,300);


    portrait->setPosition(550,100,300,200);
    portrait->setTexture(texture);

  //if(sources.size()==0)
  loadFrames();
}



void glassJoe::loadFrames()
{
        int32_t w=52,h=111;
        insert_AnimationFrame(3,1,w,h); //PASSIVE_LEFT_UP_ZERO
        insert_AnimationFrame(45,1,w,h);//PASSIVE_LEFT_UP_ONE
        insert_AnimationFrame(89,1,w,h);//PASSIVE_LEFT_UP_TWO

        insert_AnimationFrame(140,1,w,h); //PASSIVE_RIGHT_UP_ZERO
        insert_AnimationFrame(187,1,w,h); //PASSIVE_RIGHT_UP_ONE
        insert_AnimationFrame(230,1,w,h); //PASSIVE_RIGHT_UP_TWO

        insert_AnimationFrame(282,1,w,h); //PASSIVE_BOTH_UP_ZERO
        insert_AnimationFrame(326,1,w,h); //PASSIVE_BOTH_UP_ONE
        insert_AnimationFrame(368,1,w,h); //PASSIVE_BOTH_UP_TWO

        insert_AnimationFrame(421,1,w,h); //PASSIVE_BOTH_DOWN_ZERO
        insert_AnimationFrame(465,1,w,h);//PASSIVE_BOTH_DOWN_ONE
        insert_AnimationFrame(508,1,w,h);//PASSIVE_BOTH_DOWN_TWO

        insert_AnimationFrame(1,114,w,h); //STRAIGHT_PUNCH_ZERO
        insert_AnimationFrame(42,114,w,h);//STRAIGHT_PUNCH_ONE
        insert_AnimationFrame(84,114,w,h); //STRAIGHT_PUNCH_TWO
        insert_AnimationFrame(126,114,w,h);//STRAIGHT_PUNCH_THREE
        insert_AnimationFrame(170,114,w,h);//STRAIGHT_PUNCH_FOUR
        insert_AnimationFrame(217,114,w,h);//STRAIGHT_PUNCH_FIVE,

        insert_AnimationFrame(6,224,w,h);//HOOK_ZERO
        insert_AnimationFrame(53,224,w,h); //HOOK_ONE
        insert_AnimationFrame(95,224,w,h); //HOOK_TWO
        insert_AnimationFrame(139,224,w,h);//HOOK_FOUR,

        insert_AnimationFrame(227,330,w,h);// MOUTH_OPEN_BOTH_DOWN_ZERO
        insert_AnimationFrame(265,330,w,h); ///MOUTH_OPEN_BOTH_DOWN_ONE
        insert_AnimationFrame(312,330,w,h); //MOUTH_OPEN_BOTH_DOWN_TWO

        insert_AnimationFrame(2,442,w,h);//BLOCKED_DOWN_ZERO,
        insert_AnimationFrame(45,442,w,h);//BLOCKED_DOWN_ONE
        insert_AnimationFrame(97,439,w,h);//BLOCKED_UP_ZERO
        insert_AnimationFrame(142,440,w,h);//BLOCKED_UP_ONE
        insert_AnimationFrame(187,440,w,h); //BLOCKED_UP_TWO,

        insert_AnimationFrame(5,555,w,h); //PUNCHED_GUT
        insert_AnimationFrame(47,555,w,h); //PUNCHED_SHOCKED
        insert_AnimationFrame(88,555,w,h);//PUNCHED_FACE_ZERO
        insert_AnimationFrame(142,556,w,h);//PUNCHED_FACE_ONE

        insert_AnimationFrame(6,664,w,h); //KO_D_FALL_ZERO
        insert_AnimationFrame(59,664,w,h);//KO_D_FALL_ONE
        insert_AnimationFrame(117,664,57,h);//KO_D_FALL_TWO

        insert_AnimationFrame(183,664,w,h);//KO_D_GETUP_ZERO
        insert_AnimationFrame(243,664,w,h);//KO_D_GETUP_ONE

        insert_AnimationFrame(47,773,w,h);// CHEER

        insert_AnimationFrame(379,541,80,77);// PORTRAIT_FINE_ZERO
        insert_AnimationFrame(462,541,80,77);// PORTRAIT_FINE_ONE

    CURRENT_FRAME=GLASS_JOE_FRAMES::PASSIVE_LEFT_UP_ZERO;
    changeFrame(CURRENT_FRAME);
    changePortraitSource(static_cast<uint32_t>(GLASS_JOE_FRAMES::PORTRAIT_FINE_ZERO));
}


void glassJoe::changeFrame(GLASS_JOE_FRAMES frame_name)
{
     CURRENT_FRAME=frame_name;
     changeSource(static_cast<int32_t>(frame_name));
}
void glassJoe::changePortraitFrame(GLASS_JOE_FRAMES portrait_name)
{
    CURRENT_FRAME=portrait_name;
    changePortraitSource(static_cast<int32_t>(portrait_name));
}
GLASS_JOE_FRAMES glassJoe::getFrameName()
{
    return CURRENT_FRAME;
}

void glassJoe::update()
{
     
    if(behavior==nullptr && _battleMode)
    {
        behavior.reset(new BehaviorTimer(this));
        behavior->onStart();
    }

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
    
    if(behavior!=nullptr && action==nullptr)
    {
        if(behavior->isActive())
        behavior->onActive();
    }
  
   
    life.update(hp);
}
void glassJoe::updatePortrait()
 {
     if(action==nullptr || action->id!=static_cast<uint32_t>(JOE_TIMER_ID::PORTRAIT_TIMER))
     {
        setAction(JOE_TIMER_ID::PORTRAIT_TIMER);
        
       
     }
     update();
     
 }

bool glassJoe::handleIncomingPunch(Punch& punch)
{
    if(_isVulnerable)
    {
        
        
        if(punch.right_side_punch)
        setTextureFlip_HORIZONTAL();

        if(punch.high_punch)
        {
            if(CURRENT_FRAME==GLASS_JOE_FRAMES::PASSIVE_BOTH_UP_ZERO || CURRENT_FRAME==GLASS_JOE_FRAMES::PASSIVE_BOTH_UP_ONE || CURRENT_FRAME==GLASS_JOE_FRAMES::PASSIVE_BOTH_UP_TWO)
            {
                    GameObject::playSound(PUNCH_OUT_SOUND::MAC_PUNCH_BLOCKED_CHUNK); 
                    action.reset(new blockedUpTimer(this));
                    action->onStart();
                          
                    return false;
            }
            else
            {
                    GameObject::playSound(PUNCH_OUT_SOUND::MAC_PUNCH_CHUNK);
                    hp-=punch.damage;
                    action.reset(new headPunchedTimer(this));
                    action->onStart();
                    
                    return true;
            }
        }
        else
        {
            if(CURRENT_FRAME==GLASS_JOE_FRAMES::PASSIVE_BOTH_DOWN_ZERO || CURRENT_FRAME==GLASS_JOE_FRAMES::PASSIVE_BOTH_DOWN_ONE || CURRENT_FRAME==GLASS_JOE_FRAMES::PASSIVE_BOTH_DOWN_TWO)
            {
                GameObject::playSound(PUNCH_OUT_SOUND::MAC_PUNCH_BLOCKED_CHUNK);   
                action.reset(new blockedDownTimer(this));
                action->onStart();
              
                return false;
            }
            else
            {
                GameObject::playSound(PUNCH_OUT_SOUND::MAC_PUNCH_CHUNK);
                action.reset(new bodyPunchedTimer(this));
                action->onStart();
               
                hp-=punch.damage;
                return true;
            }

        }
    }
    return false;
}
void glassJoe::setAction(JOE_TIMER_ID id)
{
    
     switch(id)
    {
    
        case JOE_TIMER_ID::PASSIVE_GUARD_UP_TIMER:
        action.reset(new guardUpTimer(this));
        break;
        case JOE_TIMER_ID::PASSIVE_GUARD_DOWN_TIMER:
        action.reset(new guardDownTimer(this));
        break;
        case JOE_TIMER_ID::STRAIGHT_PUNCH_TIMER:
        action.reset(new straightPunchTimer(this));
        break;
        case JOE_TIMER_ID::HOOK_PUNCH_TIMER:
        action.reset(new hookPunchTimer(this));
        break;
        case JOE_TIMER_ID::BLOCKED_DOWN_TIMER:
        action.reset(new blockedDownTimer(this));
        break;
        case JOE_TIMER_ID::BLOCKED_UP_TIMER:
        action.reset(new blockedUpTimer(this));
        break;
        case JOE_TIMER_ID::KO_FALL_TIMER:
        action.reset(new KO_fallTimer(this));
        break;
        case JOE_TIMER_ID::KO_GET_UP_TIMER:
        action.reset(new KO_getUpTimer(this));
        break;
        case JOE_TIMER_ID::CHEER_TIMER:
        action.reset(new cheerTimer(this));
        break;
        case JOE_TIMER_ID::BODY_PUNCHED_TIMER:
        action.reset(new bodyPunchedTimer(this));
        break;
        case JOE_TIMER_ID::HEAD_PUNCHED_TIMER:
        action.reset(new headPunchedTimer(this));
        break;
        case JOE_TIMER_ID::INTRO_TIMER:
        action.reset(new IntroTimer(this));
        break;
        case JOE_TIMER_ID::MOVE_TO_NEUTRAL_POSITION_TIMER:
        action.reset(new walkToNeutralPosition(this,positions[NEUTRAL_POSITION].x,positions[NEUTRAL_POSITION].y));
        break;
        case JOE_TIMER_ID::MOVE_TO_BATTLE_POSITION_TIMER:
        action.reset(new walkToBattlePosition(this,positions[BATTLE_POSITION].x,positions[BATTLE_POSITION].y));
        break;
        case JOE_TIMER_ID::PORTRAIT_TIMER:
        action.reset(new portraitAnimationTimer(this));
        break;
        default:
        std::cerr<<"Should not come here glassJoe.cpp line 52\n";

        
       
    }
     action->onStart();
}

void glassJoe::cheer()
{
    
    if(action!=nullptr && action->id!=static_cast<uint32_t>(JOE_TIMER_ID::CHEER_TIMER))
    setAction(JOE_TIMER_ID::CHEER_TIMER);
    else if(action==nullptr)
    setAction(JOE_TIMER_ID::CHEER_TIMER);

    _battleMode=false;
    
}

void glassJoe::IntroAnimation()
{
    setAction(JOE_TIMER_ID::INTRO_TIMER);
}
void glassJoe::moveToNeutralPosition()
{
    setAction(JOE_TIMER_ID::MOVE_TO_NEUTRAL_POSITION_TIMER);
}
void glassJoe::moveToBattlePosition()
{
    setAction(JOE_TIMER_ID::MOVE_TO_BATTLE_POSITION_TIMER);
}
bool glassJoe::isInNeutralPosition()
{
   return(getXposition()==positions[NEUTRAL_POSITION].x && getYposition()==positions[NEUTRAL_POSITION].y);
}
