#ifndef __PUNCH_OUT_FIGHT_MANAGER__
#define __PUNCH_OUT_FIGHT_MANAGER__


/* C system includes */

/* C++ system includes */
#include <memory>
/* Third-party includes */

/* Own includes */

/* Forward Declaration */
class Referee;
class Ring;
class Round;
class PointSystem;
class lilMac;
class Boxer;
class Text;
/*                    */




 enum class FIGHT_STATE
{
    INTRODUCTION,
    PRE_FIGHT,
    FIGHT,
    CORNER,
    KO,
    DECISION
};


class FightManager
{
public:
    FightManager()=default;
    ~FightManager()=default;
    void init(lilMac*& Player);
   
    void fightNight();
    void draw();

    bool changeToMenuState();
    void free_allocated_memory();
    
    void Enter_pressed();


private:
    void introduction();
    void preFight();
    void fight();
    void corner();
    void KO();
    void decision();
    bool opponentIntroActivated=false;
    bool start_only_once=false;
    bool _cheer_only_once=false;
    bool _FIGHT_OVER=false;
FIGHT_STATE currentState=FIGHT_STATE::INTRODUCTION;

Ring* ring;
Round* round;

lilMac* player;
Boxer* opponent;

Referee* mario;

PointSystem* points;

Text* playerName;
Text* opponentName;
Text* player_win_lose_ko;
Text* opponent_win_lose_ko;
Text* versus;
Text* instructions;
Text* trainer;
//////

};

//




#endif