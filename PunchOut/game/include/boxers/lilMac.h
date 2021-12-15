#ifndef __PUNCH_OUT_LILMAC__
#define __PUNCH_OUT_LILMAC__

/* C system includes */

/* C++ system includes */

/* Third-party includes */

/* Own includes */
#include "Boxer.h"
#include "../../../engine/include/Text.h"
/* Forward Declaration */

/**/




enum class MAC_TIMER_ID
{
    DODGE_TIMER=0x000000000,
    DEFAULT_TIMER,
    BODY_SHOT_TIMER,
    HEAD_SHOT_TIMER,
    SUPER_SHOT_TIMER,
    TIRED_TIMER,
    PUNCHED_TIMER,
    KO_DTIMER,
    CHEER_TIMER,
    CAN_DODGE_AFTER_BLOCK_TIMER,
    BLOCK_TIMER,
    DODGE_AFTER_BLOCK_TIMER=0x000000009,
    MOVE_TO_NEUTRAL_POSITION_TIMER,
    MOVE_TO_BATTLE_POSITION_TIMER,
    PORTRAIT_TIMER
};

enum class LIL_MAC_FRAMES
{
    PASSIVE_ZERO,
    PASSIVE_ONE,
    DODGE_ZERO, // invulnarability ends
    DODGE_ONE,
    DODGE_TWO,
    BLOCK_ZERO,
    BLOCK_ONE,
    BLOCK_TWO,
    BODY_SHOT_ZERO,
    BODY_SHOT_ONE,
    BODY_SHOT_TWO, //punch lands
    HEAD_SHOT_ZERO,
    HEAD_SHOT_ONE,
    HEAD_SHOT_TWO, //punch lands
    SUPER_SHOT_ZERO,
    SUPER_SHOT_ONE,
    SUPER_SHOT_TWO,
    SUPER_SHOT_THREE,
    SUPER_SHOT_FOUR,
    SUPER_SHOT_FIVE, //punch lands
    TIRED_ZERO,
    TIRED_ONE,
    PUNCHED_ZERO,
    PUNCHED_ONE,
    KO,
    VICTORY_ZERO,
    VICTORY_ONE,

    PORTRAIT_GREAT_ZERO,
    PORTRAIT_GREAT_ONE,
    PORTRAIT_GREAT_TWO,
    PORTRAIT_GREAT_THREE,

    PORTRAIT_FINE_ZERO,
    PORTRAIT_FINE_ONE,
    PORTRAIT_FINE_TWO,
    PORTRAIT_FINE_THREE,

    PORTRAIT_TERRIBLE_ZERO,
    PORTRAIT_TERRIBLE_ONE,
    PORTRAIT_TERRIBLE_TWO,
    PORTRAIT_TERRIBLE_THREE,

};



class lilMac : public Boxer
{
    public:
        

        void init();
        void update() override;
        void updatePortrait() override;
        void  cheer()override;
        void  IntroAnimation()override;
        bool  isInNeutralPosition()override;
      
        void  moveToNeutralPosition()override;
        void  moveToBattlePosition()override;
    
        void loadFrames() override;
        bool handleIncomingPunch(Punch& punch) override;
        void draw() override;

        void dodgeLeft();
        void dodgeRight();
        void bodyShotLeft();
        void bodyShotRight();
        void headShotLeft();
        void headShotRight();
        void superShot();
        void block();
        void unblock();
        void rested();
        
        void setMaxHearts(int32_t Hearts);
        void decreaseHearts(int32_t amount);
        
        void changeFrame(LIL_MAC_FRAMES frame_name);
        void changePortraitFrame(LIL_MAC_FRAMES portrait_name);
        LIL_MAC_FRAMES getFrameName();
        void setAction(MAC_TIMER_ID id);
        void setSpecialAction(MAC_TIMER_ID id);
        
       
   
    private:
    void dodge();
    void bodyShot();
    void headShot();

    
    int32_t hearts;
    int32_t max_hearts;
    int32_t stars;
    LIL_MAC_FRAMES CURRENT_FRAME;

 std::unique_ptr<PunchOutBehaviorTimer> specialTimer;
 
    Text heartsRepresentation;
    Text startsRepresentation;

  
};

#endif