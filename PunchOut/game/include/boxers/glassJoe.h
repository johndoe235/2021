#ifndef __PUNCH_OUT_GLASS_JOE__
#define __PUNCH_OUT_GLASS_JOE__

#include "Boxer.h"

enum class JOE_TIMER_ID
{
   
    PASSIVE_LEFT_UP_TIMER,
    PASSIVE_RIGHT_UP_TIMER,
    PASSIVE_GUARD_UP_TIMER,
    PASSIVE_GUARD_DOWN_TIMER,
    STRAIGHT_PUNCH_TIMER,
    HOOK_PUNCH_TIMER,
    BLOCKED_DOWN_TIMER,
    BLOCKED_UP_TIMER,
    KO_FALL_TIMER,
    KO_GET_UP_TIMER,
    CHEER_TIMER,
    BODY_PUNCHED_TIMER,
    HEAD_PUNCHED_TIMER,
    BEHAVIOR_TIMER,
    INTRO_TIMER,
    MOVE_TO_NEUTRAL_POSITION_TIMER,
    MOVE_TO_BATTLE_POSITION_TIMER,
    PORTRAIT_TIMER
    
};



enum class GLASS_JOE_FRAMES
{
   PASSIVE_LEFT_UP_ZERO,
   PASSIVE_LEFT_UP_ONE,
   PASSIVE_LEFT_UP_TWO,

   PASSIVE_RIGHT_UP_ZERO,
   PASSIVE_RIGHT_UP_ONE,
   PASSIVE_RIGHT_UP_TWO,

   PASSIVE_BOTH_UP_ZERO,
   PASSIVE_BOTH_UP_ONE,
   PASSIVE_BOTH_UP_TWO,

   PASSIVE_BOTH_DOWN_ZERO,
   PASSIVE_BOTH_DOWN_ONE,
   PASSIVE_BOTH_DOWN_TWO,

   STRAIGHT_PUNCH_ZERO,
   STRAIGHT_PUNCH_ONE,
   STRAIGHT_PUNCH_TWO,
   STRAIGHT_PUNCH_THREE,
   STRAIGHT_PUNCH_FOUR,
   STRAIGHT_PUNCH_FIVE, //PUNCH LANDS

   HOOK_ZERO,
   HOOK_ONE,
   HOOK_TWO, //PUNCH LANDS
   HOOK_THREE, //HITTABLE

   MOUTH_OPEN_BOTH_DOWN_ZERO,
   MOUTH_OPEN_BOTH_DOWN_ONE,
   MOUTH_OPEN_BOTH_DOWN_TWO,

   BLOCKED_DOWN_ZERO,
   BLOCKED_DOWN_ONE,
   BLOCKED_UP_ZERO,
   BLOCKED_UP_ONE,
   BLOCKED_UP_TWO,


   PUNCHED_GUT,
   PUNCHED_SHOCKED,
   PUNCHED_FACE_ZERO,
   PUNCHED_FACE_ONE,

   KO_D_FALL_ZERO,
   KO_D_FALL_ONE,
   KO_D_FALL_TWO,

   KO_D_GETUP_ZERO,
   KO_D_GETUP_ONE,

   CHEER,

    PORTRAIT_FINE_ZERO,
    PORTRAIT_FINE_ONE,

    SIZE_OF_GLASS_JOE_FRAMES,

    PORTRAIT_TERRIBLE_ZERO, //not implemented
    PORTRAIT_TERRIBLE_ONE, //not implemented don't forget to switch places with SIZE_OF_GLASS_JOE_FRAMES

  
};

class glassJoe :public Boxer
{
public:
    void init();
    void update();
    void updatePortrait() override;
    void loadFrames() override;
   
    void cheer() override;
  
    bool isInNeutralPosition()override;
    void IntroAnimation() override;
    void moveToNeutralPosition() override;
    void moveToBattlePosition() override;

    bool handleIncomingPunch(Punch& punch) override;
    GLASS_JOE_FRAMES getFrameName();

    void changeFrame(GLASS_JOE_FRAMES frame_name);
    void changePortraitFrame(GLASS_JOE_FRAMES portrait_name);
 


    void setAction(JOE_TIMER_ID id);


private:
    int32_t getUpStrength=3;
    
    GLASS_JOE_FRAMES CURRENT_FRAME;
    std::unique_ptr<PunchOutBehaviorTimer> behavior;

   
};

#endif
