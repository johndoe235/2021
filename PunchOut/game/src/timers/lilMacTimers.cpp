#include "../../include/timers/lilMacTimers.h"
#include "../../../engine/include/Timer.h"
#include "../../include/boxers/lilMac.h"

#include "../../include/Resources.h"
#include <iostream>
#include <cmath>




#define JUMP_DISTANCE 50
#define DAMAGE 1
#define NORMAL_PUNCH_POINT 10

using namespace lilMacTimers;

dodgeTimer::dodgeTimer(lilMac* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(MAC_TIMER_ID::DODGE_TIMER)),mac(fighter)
{
    desired_distance=mac->getWidth()/3;
    startingX=mac->getXposition();
    startingY=mac->getYposition();
    total_duration=400;
    mac->Lock();
    mac->makeInvulnerable();
    GameObject::playSound(PUNCH_OUT_SOUND::MAC_DODGE_CHUNK);

}
dodgeTimer::~dodgeTimer()
{
     
    mac->makeVulnerable();
    mac->changeFrame(LIL_MAC_FRAMES::PASSIVE_ONE);

    if(mac->isTextureFlipped())
    mac->setTextureFlip_NONE();

    mac->setXposition(startingX);
    mac->setYposition(startingY);
    mac->Unlock();
}
void dodgeTimer::onActive()
{
   // uint32_t remaining_mili_seconds=remaining_ms();

    if(desired_distance>0 && !shouldReturn)
    {
        if(mac->isTextureFlipped())
        mac->moveRight(10);
        else
        mac->moveLeft(10);

        desired_distance-=10;
    }
    else if(shouldReturn && desired_distance<mac->getWidth()/3)
    {
        
        if(mac->isTextureFlipped())
        mac->moveLeft(10);
        else
        mac->moveRight(10);

        desired_distance+=10;
    }

    if(remaining_ms()>280)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::DODGE_ZERO)
        {
            mac->changeFrame(LIL_MAC_FRAMES::DODGE_ZERO);
            mac->moveUp(5);

            
        }
        
           
    }
    else if(remaining_ms()>250)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::DODGE_ONE)
        {
            

            mac->changeFrame(LIL_MAC_FRAMES::DODGE_ONE);
            mac->moveDown(5);

           

        }

       
    }
    else if(remaining_ms()>100)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::DODGE_TWO)
        {
            mac->changeFrame(LIL_MAC_FRAMES::DODGE_TWO);
           mac->moveUp(5);
           
            
        }
        
    }
    else if(remaining_ms()>50)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::DODGE_ONE)
        {
             mac->changeFrame(LIL_MAC_FRAMES::DODGE_ONE);
             
           shouldReturn=true;
               
        }
       
      
    }
    else
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::DODGE_ZERO)
        {
            mac->changeFrame(LIL_MAC_FRAMES::DODGE_ZERO);
          mac->moveDown(10);
          
        }
          
    }

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 defaultTimer::defaultTimer(lilMac* fighter)
 :PunchOutBehaviorTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(MAC_TIMER_ID::DEFAULT_TIMER)),mac(fighter)
{
    total_duration=300;
    loops=-1;
  
}
defaultTimer::~defaultTimer()
{
    if(x_offset!=0)
    mac->moveLeft(-x_offset);
}
void defaultTimer::onActive()
{
    LIL_MAC_FRAMES temp=mac->getFrameName();
    
    if(passed_ms()<lastanimation)
    lastanimation=0;

    if(passed_ms()>lastanimation+300)
    {
        if(temp==LIL_MAC_FRAMES::PASSIVE_ONE)
        {
            mac->changeFrame(LIL_MAC_FRAMES::PASSIVE_ZERO);
            randomize_step();
        }
        else if(temp==LIL_MAC_FRAMES::PASSIVE_ZERO)
        {
            mac->changeFrame(LIL_MAC_FRAMES::PASSIVE_ONE);
            randomize_step();
        }
        lastanimation=passed_ms();
    }   
}
void defaultTimer::randomize_step()
{
    if(x_offset!=0)
    {
        mac->moveLeft(-x_offset);
        x_offset=0;
    }
    std::srand(timer::GetTicks());
    x_offset=rand()%10;
    if( (rand()%100)%5==0)x_offset*=-1;
    mac->moveLeft(x_offset);
    total_duration=rand()%100+300;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bodyShotTimer::bodyShotTimer(lilMac* fighter)
 :PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(MAC_TIMER_ID::BODY_SHOT_TIMER)),mac(fighter)
{
    total_duration=400;
    mac->Lock();
}
bodyShotTimer::~bodyShotTimer()
{
    mac->Unlock();
    mac->setTextureFlip_NONE();
    mac->changeFrame(LIL_MAC_FRAMES::PASSIVE_ONE);
}
void bodyShotTimer::onActive()
{
    if(remaining_ms()>350)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::BODY_SHOT_ZERO)
            mac->changeFrame(LIL_MAC_FRAMES::BODY_SHOT_ZERO);
    }
    else if(remaining_ms()>300)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::BODY_SHOT_ONE)
            mac->changeFrame(LIL_MAC_FRAMES::BODY_SHOT_ONE);
    }
    else if(remaining_ms()>100)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::BODY_SHOT_TWO)
        {
             mac->setPunchInfo(mac->isTextureFlipped(),false,DAMAGE,NORMAL_PUNCH_POINT);
             mac->punchIsLanding();
             mac->changeFrame(LIL_MAC_FRAMES::BODY_SHOT_TWO);
        }
    }
    else if(remaining_ms()>50)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::BODY_SHOT_ONE)
        {
            mac->punchNOTLanding();
            mac->changeFrame(LIL_MAC_FRAMES::BODY_SHOT_ONE); 
        }
    }
    else
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::BODY_SHOT_ZERO)
        mac->changeFrame(LIL_MAC_FRAMES::BODY_SHOT_ZERO); 
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


headShotTimer::headShotTimer(lilMac* fighter)
 :PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(MAC_TIMER_ID::HEAD_SHOT_TIMER)),mac(fighter)
{
    total_duration=400;
    hasMovedOnce=false;
    hasMovedTwice=false;

    mac->Lock();
}
headShotTimer::~headShotTimer()
{
    mac->Unlock();
    if(hasMovedOnce)
        mac->moveDown(JUMP_DISTANCE);
    if(hasMovedTwice)
        mac->moveDown(JUMP_DISTANCE);

    mac->Unlock();
    mac->setTextureFlip_NONE();
    mac->changeFrame(LIL_MAC_FRAMES::PASSIVE_ONE);
}

void headShotTimer::onActive()
{
    if(remaining_ms()>350)
    {
        mac->changeFrame(LIL_MAC_FRAMES::HEAD_SHOT_ZERO);
    }
    else if(remaining_ms()>300)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::HEAD_SHOT_ONE)
        {
         mac->changeFrame(LIL_MAC_FRAMES::HEAD_SHOT_ONE);
         mac->moveUp(JUMP_DISTANCE);
         hasMovedOnce=true;
         }
    
    }
    else if(remaining_ms()>150)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::HEAD_SHOT_TWO)
        {
            mac->punchIsLanding();
            mac->setPunchInfo(mac->isTextureFlipped(),true,DAMAGE,NORMAL_PUNCH_POINT);
            mac->changeFrame(LIL_MAC_FRAMES::HEAD_SHOT_TWO);
            mac->moveUp(JUMP_DISTANCE);
            hasMovedTwice=true;
        }
         
         
    
    }
    else if(remaining_ms()>100)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::HEAD_SHOT_ONE)
        {
            mac->punchNOTLanding();
            if(hasMovedTwice)
            {
                mac->moveDown(JUMP_DISTANCE);
                hasMovedTwice=false;
            }
            mac->changeFrame(LIL_MAC_FRAMES::HEAD_SHOT_ONE); 
        }
        
    }
    else if(remaining_ms()>50)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::HEAD_SHOT_ZERO)
        {
            mac->changeFrame(LIL_MAC_FRAMES::HEAD_SHOT_ZERO); 
            if(hasMovedOnce)
            {
                mac->moveDown(JUMP_DISTANCE);
                hasMovedOnce=false;
            }
        }
    }

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

superShotTimer::superShotTimer(lilMac* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(MAC_TIMER_ID::SUPER_SHOT_TIMER))
 {
     mac=fighter;
     total_duration=600;
 }
superShotTimer::~superShotTimer()
{
    mac->Unlock();
}
void superShotTimer::onActive()
{
        if(remaining_ms()>6500)
        {
            mac->changeFrame(LIL_MAC_FRAMES::SUPER_SHOT_ZERO);
        }
        else if(remaining_ms()>550)
        {
            mac->changeFrame(LIL_MAC_FRAMES::SUPER_SHOT_ONE);
        }
        else if(remaining_ms()>450)
        {
            mac->changeFrame(LIL_MAC_FRAMES::SUPER_SHOT_TWO);
        }
        else if(remaining_ms()>350)
        {
            mac->changeFrame(LIL_MAC_FRAMES::SUPER_SHOT_THREE);
        }
        else if(remaining_ms()>250)
        {
            mac->changeFrame(LIL_MAC_FRAMES::SUPER_SHOT_FOUR);
        }
        else if(remaining_ms()>0)
        {
        mac->changeFrame(LIL_MAC_FRAMES::SUPER_SHOT_FIVE);
        }
}
void superShotTimer::onExpire()
{
    mac->Unlock();
    mac->changeFrame(LIL_MAC_FRAMES::PASSIVE_ONE);
}
void superShotTimer::onStart()
{
    mac->Lock();
    start_timer(total_duration);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 tiredTimer::tiredTimer(lilMac* fighter)
 :PunchOutBehaviorTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(MAC_TIMER_ID::TIRED_TIMER)),mac(fighter)
 {
     total_duration=400;
     loops=4;
     
 }
 
void tiredTimer::onActive()
{
    if(remaining_ms()>200)
    {
        mac->changeFrame(LIL_MAC_FRAMES::TIRED_ZERO);
    }
    else if(remaining_ms()>0)
    {
        mac->changeFrame(LIL_MAC_FRAMES::TIRED_ONE);
    }
}

void tiredTimer::onExpire()
{
    mac->rested();
    mac->changeFrame(LIL_MAC_FRAMES::PASSIVE_ONE);
    
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
punchedTimer::punchedTimer(lilMac* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(MAC_TIMER_ID::PUNCHED_TIMER)),mac(fighter)
{
    total_duration=400;
    mac->Lock();
    mac->makeInvulnerable();

    if(mac->getHP()<=0)resetAction=false;
}

punchedTimer::~punchedTimer()
{
    
        //mac->Unlock();
        //mac->changeFrame(LIL_MAC_FRAMES::PASSIVE_ZERO);
    
    
    
}
void punchedTimer::onActive()
{
    if(remaining_ms()>200)
    {
        mac->changeFrame(LIL_MAC_FRAMES::PUNCHED_ZERO);

    }
    else if(remaining_ms()>0)
    {
        mac->changeFrame(LIL_MAC_FRAMES::PUNCHED_ONE);
    }

}
void punchedTimer::onExpire()
{
    if(mac->getHP()>0)
    {
        mac->Unlock();
        mac->makeVulnerable();
        mac->changeFrame(LIL_MAC_FRAMES::PASSIVE_ZERO);
    }
    else
    {
    
        mac->setAction(MAC_TIMER_ID::KO_DTIMER);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cheerTimer::cheerTimer(lilMac* fighter)
:PunchOutTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(MAC_TIMER_ID::CHEER_TIMER)),mac(fighter)
{
    total_duration=800;
    loops=12;
    mac->Lock();
   
}
cheerTimer::~cheerTimer()
{
    mac->Unlock();
}
void cheerTimer::onActive()
{
 

    if(remaining_ms()>200)
    {
        mac->changeFrame(LIL_MAC_FRAMES::VICTORY_ZERO);
    }
    else if(remaining_ms()>0)
    {
        mac->changeFrame(LIL_MAC_FRAMES::VICTORY_ONE);

    }
}
void cheerTimer::onExpire()
{
    mac->endCheer();
}
    


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


KO_dTimer::KO_dTimer(lilMac* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(MAC_TIMER_ID::KO_DTIMER)),mac(fighter)
{
   
    resetAction=false;
    total_duration=1900;
}
KO_dTimer::~KO_dTimer()
{
    
}

void KO_dTimer::onActive()
{
    if(mac->getYposition()<640/*SCREEN HEIGHT*/)
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::KO)
            mac->changeFrame(LIL_MAC_FRAMES::KO);


        mac->moveDown(5);
    }
    else
    {
        mac->KO();
        expireNow();
    }

    

}
void KO_dTimer::onExpire()
{
        
}
void KO_dTimer::onStart()
{
    mac->Lock();
    start_timer(total_duration);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


canDodgeAfterBlockTimer::canDodgeAfterBlockTimer()
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(MAC_TIMER_ID::CAN_DODGE_AFTER_BLOCK_TIMER))
{
   
    total_duration=200;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 blockTimer::blockTimer(lilMac* fighter)
 :PunchOutTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(MAC_TIMER_ID::BLOCK_TIMER)),mac(fighter)
 {
    
     total_duration=110;
     loops=-1;
     mac->Lock();
 }
blockTimer::~blockTimer()
{
    mac->Unlock();
   
}


void blockTimer::onActive()
{
    if(remaining_ms()>0)
    {
        if(!animate_only_once)
        {
        mac->changeFrame(LIL_MAC_FRAMES::BLOCK_ZERO);
        animate_only_once=true;
        }
    }
    else
    {
        if(mac->getFrameName()!=LIL_MAC_FRAMES::BLOCK_ONE)
        mac->changeFrame(LIL_MAC_FRAMES::BLOCK_ONE);
    }
}
void blockTimer::onStart()
{
    mac->Lock();
    start_timer(total_duration);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
dodgeAfterBlockTimer::dodgeAfterBlockTimer(lilMac* fighter)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(MAC_TIMER_ID::DODGE_AFTER_BLOCK_TIMER)),mac(fighter)
{
    total_duration=400;
     GameObject::playSound(PUNCH_OUT_SOUND::MAC_DODGE_CHUNK);
}

void dodgeAfterBlockTimer::onActive()
{
    mac->changeFrame(LIL_MAC_FRAMES::BLOCK_TWO);
}
void dodgeAfterBlockTimer::onExpire()
{
    mac->Unlock();
    mac->makeVulnerable();
    mac->changeFrame(LIL_MAC_FRAMES::PASSIVE_ONE);
}
void dodgeAfterBlockTimer::onStart()
{
    mac->Lock();
    mac->makeInvulnerable();
    start_timer(total_duration);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
walkToNeutralPosition::walkToNeutralPosition(lilMac* fighter,int destX,int destY)
:PunchOutTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(MAC_TIMER_ID::MOVE_TO_NEUTRAL_POSITION_TIMER)),mac(fighter),desiredX(destX),desiredY(destY)
{
    total_duration=600;
    loops=-1;
    mac->Lock();
   
      animations[0]=static_cast<uint32_t>(LIL_MAC_FRAMES::PASSIVE_ZERO);
      animations[1]=static_cast<uint32_t>(LIL_MAC_FRAMES::PASSIVE_ONE);
}

void walkToNeutralPosition::onActive()
{
     if(last_animation>passed_ms())
        last_animation=0;

    if(passed_ms()<last_animation+400)
    {
        mac->changeFrame(static_cast<LIL_MAC_FRAMES>(animations[current_frame++]));
        
        last_animation=passed_ms();
        if(current_frame>=frame_count)
        current_frame=0;
    }
    
    if(mac->getYposition()<desiredY)
    {
        mac->moveDown(1);
    }
       
    if(mac->getYposition()==desiredY)
        expireNow();
    
   

}
void walkToNeutralPosition::onExpire()
{
 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

walkToBattlePosition::walkToBattlePosition(lilMac* fighter,int destX,int destY)
:PunchOutTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(MAC_TIMER_ID::MOVE_TO_BATTLE_POSITION_TIMER)),mac(fighter),desiredX(destX),desiredY(destY)
{
    total_duration=600;
    loops=4;
    mac->Lock();

    animations[0]=static_cast<uint32_t>(LIL_MAC_FRAMES::PASSIVE_ZERO);
    animations[1]=static_cast<uint32_t>(LIL_MAC_FRAMES::PASSIVE_ONE);
}

void walkToBattlePosition::onActive()
{
    if(last_animation>passed_ms())
        last_animation=0;

    if(passed_ms()>last_animation+100)
    {
        mac->changeFrame(static_cast<LIL_MAC_FRAMES>(animations[current_frame++]));
        
        last_animation=passed_ms();
        if(current_frame>=frame_count)
        current_frame=0;

         if(mac->getYposition()>desiredY)
        {
            if(mac->getYposition()-10>desiredY)
            mac->moveUp(10);
            else
            expireNow();
            
        }
    }
    
    
   
       
    
    
}
void walkToBattlePosition::onExpire()
{
    mac->Unlock();
    mac->setYposition(desiredY);
    mac->setSpecialAction(MAC_TIMER_ID::DEFAULT_TIMER);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

portraitAnimationTimer:: portraitAnimationTimer(lilMac* fighter)
:PunchOutTimer(TIMER_TYPE_ID::REPEATING,static_cast<uint32_t>(MAC_TIMER_ID::PORTRAIT_TIMER)),mac(fighter)
{
    total_duration=800;
    loops=-1;
}
void portraitAnimationTimer::onActive()
{
    if(passed_ms()>600)
    {
        mac->changePortraitFrame(LIL_MAC_FRAMES::PORTRAIT_GREAT_THREE);
    }
    else if(passed_ms()>400)
    {
        mac->changePortraitFrame(LIL_MAC_FRAMES::PORTRAIT_GREAT_TWO);

    }
    else if(passed_ms()>200)
    {
        mac->changePortraitFrame(LIL_MAC_FRAMES::PORTRAIT_GREAT_ONE);
    }
    else if(passed_ms()>0)
    {
        mac->changePortraitFrame(LIL_MAC_FRAMES::PORTRAIT_GREAT_ZERO);
    }
}
