#include "../../include/timers/glassJoeTimers.h"
#include "../../include/boxers/glassJoe.h"
#include "../../../engine/include/Timer.h"
#include "../../include/Resources.h"
#include <iostream>
#include <cmath>
using namespace glassJoeTimers;


#define STRAIGHT_DMG 10
#define HOOK_DMG 20

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    straightPunchTimer::straightPunchTimer(glassJoe* fighter)
    :PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::STRAIGHT_PUNCH_TIMER)),joe(fighter)
    {
        total_duration=1000;
         
    }
    straightPunchTimer::~straightPunchTimer()
    {
        joe->moveUp(30); 
        joe->moveRight(20);
        joe->punchNOTLanding();
        joe->makeVulnerable();
    }
    void straightPunchTimer::onActive()
    {
        if(remaining_ms()>700)
        {

            if(joe->getFrameName()!=GLASS_JOE_FRAMES::STRAIGHT_PUNCH_ZERO)
            {
            joe->makeInvulnerable();
            joe->changeFrame(GLASS_JOE_FRAMES::STRAIGHT_PUNCH_ZERO);
            joe->moveUp(20);
            joe->moveLeft(20);
            }
        }
        else if(remaining_ms()>600)
        {
            if(joe->getFrameName()!=GLASS_JOE_FRAMES::STRAIGHT_PUNCH_ONE)
            joe->changeFrame(GLASS_JOE_FRAMES::STRAIGHT_PUNCH_ONE);
        }   
        else if(remaining_ms()>500)
        {   
            if(joe->getFrameName()!=GLASS_JOE_FRAMES::STRAIGHT_PUNCH_TWO)
            joe->changeFrame(GLASS_JOE_FRAMES::STRAIGHT_PUNCH_TWO);
        }
        else if(remaining_ms()>400)
        {
            if(joe->getFrameName()!=GLASS_JOE_FRAMES::STRAIGHT_PUNCH_THREE)
            joe->changeFrame(GLASS_JOE_FRAMES::STRAIGHT_PUNCH_THREE);
        }
        else if(remaining_ms()>300)
        {
            if(joe->getFrameName()!=GLASS_JOE_FRAMES::STRAIGHT_PUNCH_FOUR)
            joe->changeFrame(GLASS_JOE_FRAMES::STRAIGHT_PUNCH_FOUR);
        }
        else if(remaining_ms()>50)
        {
            if(joe->getFrameName()!=GLASS_JOE_FRAMES::STRAIGHT_PUNCH_FIVE)
            {
            joe->punchIsLanding();
            GameObject::playSound(PUNCH_OUT_SOUND::OPPONENT_PUNCH);
            joe->changeFrame(GLASS_JOE_FRAMES::STRAIGHT_PUNCH_FIVE);
            joe->setPunchInfo(false,false,STRAIGHT_DMG,0);
            joe->moveDown(50);
           
            }
        }
        else
        {
             joe->makeVulnerable();
             joe->punchNOTLanding();
        }
       
       

    }
    void straightPunchTimer::onExpire()
    {
        joe->punchNOTLanding();
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 hookPunchTimer::hookPunchTimer(glassJoe* fighter)
 :PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::HOOK_PUNCH_TIMER)),joe(fighter)
 {
     total_duration=1200;
     joe->makeInvulnerable();
 }
void hookPunchTimer::onActive()
{
    if(remaining_ms()>800)
    {
        if(joe->getFrameName()!=GLASS_JOE_FRAMES::HOOK_ZERO)
        {
            joe->changeFrame(GLASS_JOE_FRAMES::HOOK_ZERO);
            joe->moveLeft(70);
            joe->moveUp(20);
        }
    }
    else if(remaining_ms()>600)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::HOOK_ONE);
    }
    else if(remaining_ms()>400)
    {
        if(joe->getFrameName()!=GLASS_JOE_FRAMES::HOOK_TWO)
        {
        joe->punchIsLanding();
        joe->setPunchInfo(false,false,HOOK_DMG,0);
        joe->changeFrame(GLASS_JOE_FRAMES::HOOK_TWO);
    
        joe->moveRight(70);
        joe->moveDown(20);
        GameObject::playSound(PUNCH_OUT_SOUND::OPPONENT_PUNCH);
        }
    }
    else if(remaining_ms()>300)
    {
        if(joe->getFrameName()!=GLASS_JOE_FRAMES::HOOK_THREE)
        {
        joe->makeVulnerable();
        joe->punchNOTLanding();
        joe->changeFrame(GLASS_JOE_FRAMES::HOOK_THREE);
        }
    }
}
void hookPunchTimer::onExpire()
{
    //joe->changeFrame(GLASS_JOE_FRAMES::PASSIVE_LEFT_UP_ZERO);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
blockedDownTimer::blockedDownTimer(glassJoe* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::BLOCKED_DOWN_TIMER)),joe(fighter)
{
    total_duration=600; //SHOULD BE EQUAL TO LIL_MAC_PUNCH

}
blockedDownTimer::~blockedDownTimer()
{
    if(joe->isTextureFlipped())
        joe->setTextureFlip_NONE();
}
void blockedDownTimer::onActive()
{
    if(remaining_ms()>300)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::BLOCKED_DOWN_ZERO);
    }
    else if(remaining_ms()>0)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::BLOCKED_DOWN_ONE);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
blockedUpTimer::blockedUpTimer(glassJoe* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::BLOCKED_UP_TIMER)),joe(fighter)
{
 total_duration=600; //SHOULD BE EQUAL TO LIL_MAC_PUNCH
}
blockedUpTimer::~blockedUpTimer()
{
    if(joe->isTextureFlipped())
        joe->setTextureFlip_NONE();
}
void blockedUpTimer::onActive()
{
     if(remaining_ms()>300)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::BLOCKED_UP_ZERO);
    }
    else if(remaining_ms()>100)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::BLOCKED_UP_ONE);
    }
    else
    {
        joe->changeFrame(GLASS_JOE_FRAMES::BLOCKED_UP_TWO);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bodyPunchedTimer::bodyPunchedTimer(glassJoe* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::BODY_PUNCHED_TIMER)),joe(fighter)
{
    total_duration=150; 
    joe->makeInvulnerable();
}
bodyPunchedTimer::~bodyPunchedTimer()
{
    if(joe->isTextureFlipped())
        joe->setTextureFlip_NONE();
}
void bodyPunchedTimer::onActive()
{
    if(remaining_ms()>0)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::PUNCHED_GUT);
        
    }
    else
    {
        if(joe->getHP()>0)
        joe->makeVulnerable();
        else
        {
            resetAction=false;
            joe->setAction(JOE_TIMER_ID::KO_FALL_TIMER);
        }
    }
}

void bodyPunchedTimer::onExpire()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

headPunchedTimer::headPunchedTimer(glassJoe* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::HEAD_PUNCHED_TIMER)),joe(fighter)
{
    total_duration=300;
    joe->makeInvulnerable();
}
headPunchedTimer::~headPunchedTimer()
{
    
    if(joe->isTextureFlipped())
        joe->setTextureFlip_NONE();

        
}
void headPunchedTimer::onActive()
{
    if(remaining_ms()>150)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::PUNCHED_FACE_ZERO);
    }
    else if(remaining_ms()>1)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::PUNCHED_FACE_ONE);
    }
    else
    {
        if(joe->getHP()>0)
        joe->makeVulnerable();
        else
        {
            resetAction=false;
            joe->setAction(JOE_TIMER_ID::KO_FALL_TIMER);
        }
    }
}
void headPunchedTimer::onExpire()
{
 
   
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KO_fallTimer::KO_fallTimer(glassJoe* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::KO_FALL_TIMER)),joe(fighter)
{
    total_duration=1500;
    
    resetAction=false;
}
void KO_fallTimer::onActive()
{
    if(remaining_ms()>1000)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::KO_D_FALL_ZERO);
    }
    else if(remaining_ms()>500)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::KO_D_FALL_ONE);
    }
    else if(remaining_ms()>0)
    {
        if(joe->getFrameName()!=GLASS_JOE_FRAMES::KO_D_FALL_TWO)
        {
            joe->changeFrame(GLASS_JOE_FRAMES::KO_D_FALL_TWO);
            joe->KO();
        }

    }
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KO_getUpTimer::KO_getUpTimer(glassJoe* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::KO_GET_UP_TIMER)),joe(fighter)
{
    total_duration=1000;
}
void KO_getUpTimer::onActive() 
{
    if(remaining_ms()>500)
        joe->changeFrame(GLASS_JOE_FRAMES::KO_D_GETUP_ZERO);
    else if(remaining_ms()>0)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::KO_D_GETUP_ONE);
    }
    //glass joe should be returned to his normal spot

}
void KO_getUpTimer::onExpire()
{
    ///Glass Joe must have returned to the center of the ring by now.
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cheerTimer::cheerTimer(glassJoe* fighter)
:PunchOutTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(GLASS_JOE_FRAMES::CHEER)),joe(fighter)
{
    total_duration=400;
    loops=24;
 
}
void cheerTimer::onActive()
{
       
    if(remaining_ms()>200)
    {
        
        joe->changeFrame(GLASS_JOE_FRAMES::CHEER);
    }
    else if(remaining_ms()>0)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::PASSIVE_RIGHT_UP_ZERO);

    }
   
}
void cheerTimer::onExpire()
{
     
    joe->endCheer();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 guardUpTimer::guardUpTimer(glassJoe* fighter)
 :PunchOutTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(JOE_TIMER_ID::PASSIVE_GUARD_UP_TIMER)),joe(fighter)
 {
     total_duration=800;
     loops=4;
 }
void guardUpTimer::onActive()
{
    if(remaining_ms()>600)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::PASSIVE_BOTH_UP_ZERO);
    }
    else if(remaining_ms()>400)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::PASSIVE_BOTH_UP_ONE);
    }
    else if(remaining_ms()>0)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::PASSIVE_BOTH_UP_TWO);
    }
    else
    {
        reset_timer();
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 guardDownTimer::guardDownTimer(glassJoe* fighter)
 :PunchOutTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(JOE_TIMER_ID::PASSIVE_GUARD_DOWN_TIMER)),joe(fighter)
 {
     total_duration=800;
     loops=4;
 }
 
void guardDownTimer::onActive()
{
    if(remaining_ms()>600)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::PASSIVE_BOTH_DOWN_ZERO);
    }
    else if(remaining_ms()>400)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::PASSIVE_BOTH_DOWN_ONE);
    }
    else if(remaining_ms()>0)
    {
        joe->changeFrame(GLASS_JOE_FRAMES::PASSIVE_BOTH_DOWN_TWO);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



BehaviorTimer::BehaviorTimer(glassJoe* fighter)
:PunchOutBehaviorTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::BEHAVIOR_TIMER)),joe(fighter)
{
    total_duration=180000;
}
void BehaviorTimer::onActive()
{
    
    if(joe->isPlayerTired())
    {
            joe->setAction(JOE_TIMER_ID::HOOK_PUNCH_TIMER);
    }
    else if(passed_s()>60)
    {
        
          if(passed_ms()%2==0)
            joe->setAction(JOE_TIMER_ID::STRAIGHT_PUNCH_TIMER);
            else
            {
                if(passed_s()%2==0)
                joe->setAction(JOE_TIMER_ID::HOOK_PUNCH_TIMER);
                else
                {
                     if(passed_ms()%3==0)
                    joe->setAction(JOE_TIMER_ID::PASSIVE_GUARD_UP_TIMER);
                    else
                    joe->setAction(JOE_TIMER_ID::PASSIVE_GUARD_DOWN_TIMER);
                }

            }
    }
    else if(passed_s()<10)
    {
       joe->setAction(JOE_TIMER_ID::PASSIVE_GUARD_DOWN_TIMER);
    }
    else 
    {
        
        if(passed_ms()%5==0)
        {
            if(passed_ms()%2==0)
            joe->setAction(JOE_TIMER_ID::STRAIGHT_PUNCH_TIMER);
            else
             joe->setAction(JOE_TIMER_ID::HOOK_PUNCH_TIMER);
        }        
        else
        {
            if(passed_ms()%2==0)
            joe->setAction(JOE_TIMER_ID::PASSIVE_GUARD_UP_TIMER);
            else
            joe->setAction(JOE_TIMER_ID::PASSIVE_GUARD_DOWN_TIMER);
        }

    }


}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IntroTimer::IntroTimer(glassJoe* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::INTRO_TIMER)),joe(fighter)
{
    total_duration=7000;
    GameObject::playMusic(PUNCH_OUT_SOUND::GLASS_JOE_THEME);
}
void IntroTimer::onActive()
{
    if(remaining_ms()>6000)
    {
        if(joe->getFrameName()!=GLASS_JOE_FRAMES::PASSIVE_LEFT_UP_ZERO)
        {
            joe->changeFrame(GLASS_JOE_FRAMES::PASSIVE_LEFT_UP_ZERO);
        }
    }
    else if(remaining_ms()>0)
    {
         if(joe->getFrameName()!=GLASS_JOE_FRAMES::CHEER)
        {
                joe->changeFrame(GLASS_JOE_FRAMES::CHEER);
        }
    }
   
}
void IntroTimer::onExpire()
{
    joe->endIntro();
    GameObject::pauseMusic();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

walkToNeutralPosition::walkToNeutralPosition(glassJoe* fighter,int destX,int destY)
:PunchOutTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(JOE_TIMER_ID::MOVE_TO_NEUTRAL_POSITION_TIMER)),joe(fighter),desiredX(destX),desiredY(destY)
{
    total_duration=100;
    loops=-1;
   
      animations[0]=static_cast<uint32_t>(GLASS_JOE_FRAMES::PASSIVE_RIGHT_UP_ZERO);
      animations[1]=static_cast<uint32_t>(GLASS_JOE_FRAMES::PASSIVE_LEFT_UP_ZERO);
      animations[2]=static_cast<uint32_t>(GLASS_JOE_FRAMES::PASSIVE_LEFT_UP_ONE);
      animations[3]=static_cast<uint32_t>(GLASS_JOE_FRAMES::PASSIVE_LEFT_UP_TWO);
      animations[4]=static_cast<uint32_t>(GLASS_JOE_FRAMES::PASSIVE_RIGHT_UP_TWO);
      animations[5]=static_cast<uint32_t>(GLASS_JOE_FRAMES::PASSIVE_RIGHT_UP_ONE);
}

void walkToNeutralPosition::onActive()
{
     if(last_animation>passed_ms())
        last_animation=0;

    if(last_animation+60<passed_ms())
    {
        joe->changeFrame(static_cast<GLASS_JOE_FRAMES>(animations[current_frame++]));
        
        last_animation=passed_ms();

        if(current_frame>=frame_count)
        current_frame=0;
    }
    if(joe->getXposition()>desiredX)
    {
        joe->moveLeft(2);
    }
    else
    joe->setXposition(desiredX);

    if(joe->getYposition()<desiredY)
    {
        joe->moveDown(1);
    }
    else
    joe->setYposition(desiredY);
       
   
       
    
   

}
void walkToNeutralPosition::onExpire()
{
    

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

walkToBattlePosition::walkToBattlePosition(glassJoe* fighter,int destX,int destY)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(JOE_TIMER_ID::MOVE_TO_BATTLE_POSITION_TIMER)),joe(fighter),desiredX(destX),desiredY(destY)
{
    total_duration=1000;
    joe->makeInvulnerable();
    animations[0]=static_cast<uint32_t>(GLASS_JOE_FRAMES::PASSIVE_BOTH_UP_ZERO);
    animations[1]=static_cast<uint32_t>(GLASS_JOE_FRAMES::PASSIVE_BOTH_UP_ONE);
    animations[2]=static_cast<uint32_t>(GLASS_JOE_FRAMES::PASSIVE_BOTH_UP_TWO);
}

void walkToBattlePosition::onActive()
{
    if(last_animation>passed_ms())
        last_animation=0;

    if(last_animation+200<passed_ms())
    {
        joe->changeFrame(static_cast<GLASS_JOE_FRAMES>(animations[current_frame++]));
        
        last_animation=passed_ms();
        if(current_frame>=frame_count)
        current_frame=0;
    }
    if(joe->getXposition()<desiredX)
    {
        joe->moveRight(2);
    }
    else
    joe->setXposition(desiredX);

    if(joe->getYposition()<desiredY)
    {
        joe->moveDown(2);
    }
    else
    joe->setYposition(desiredY);
       
    if(joe->getXposition()==desiredX && joe->getYposition()==desiredY)
        expireNow();
    
}
void walkToBattlePosition::onExpire()
{
    
    joe->activateBattleMode();
    joe->makeVulnerable();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
portraitAnimationTimer:: portraitAnimationTimer(glassJoe* fighter)
:PunchOutTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(JOE_TIMER_ID::PORTRAIT_TIMER)),joe(fighter)
{
    total_duration=800;
    loops=-1;
    
}
void portraitAnimationTimer::onActive()
{
    
    if(passed_ms()>600)
    {
        joe->changePortraitFrame(GLASS_JOE_FRAMES::PORTRAIT_FINE_ZERO);
    }
    else
    {
          joe->changePortraitFrame(GLASS_JOE_FRAMES::PORTRAIT_FINE_ONE);
    }
}




 