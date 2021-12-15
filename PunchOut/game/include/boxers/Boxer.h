#ifndef __PUNCH_OUT_BOXER__
#define __PUNCH_OUT_BOXER__


/* C system includes */

/* C++ system includes */
#include <string>
#include <vector>
#include <memory>
#include <string>
/* Third-party includes */

/* Own includes */
#include "../../../engine/include/GameObject.h"
#include "../../include/timers/PunchOutTimer.h"
#include "../../include/fight/Lifebar.h"
#include "../../../engine/include/utils/shape/Point.h"
/* Forward Declaration */
struct SDL_Rect;
class Texture;
class Renderer;
class Image;
/**/

struct Punch
{
    bool right_side_punch;
    bool high_punch;
    int damage;
    int points;
    bool star;

};

enum POSITIONS
{
    INTRO_POSITION=0,
    NEUTRAL_POSITION=1,
    BATTLE_POSITION=2
};

class Boxer :public GameObject
{
public:
    Boxer();
    virtual ~Boxer();
    void virtual init()=0;
    void virtual update()=0;
    void virtual updatePortrait();
    void virtual loadFrames()=0;
    bool isKO_D();
    bool stoodUp();
    void KO();
    
    std::string boxerName();
    std::string win_lose_ko_();
    void makeVulnerable();
    void makeInvulnerable();
    
    void Lock();
    void Unlock();

    bool isPlayerTired();

    bool  hasPunchLanded();
    bool virtual handleIncomingPunch(Punch& punch_type)=0;
    void virtual IntroAnimation()=0;
    bool virtual isInNeutralPosition()=0;
    void virtual moveToNeutralPosition()=0;
    void virtual moveToBattlePosition()=0;


    void teleportTO_introPosition();
    void teleportTO_neutralPosition();
    void teleportTO_battlePosition();

    Punch&  punchInformation();
    void punchIsLanding();
    void punchNOTLanding();
    void setPunchInfo(bool right,bool high,int dmg,int points);

    bool hasIntroEnded();
    void activateBattleMode();
    void virtual cheer()=0;
    
    bool  hasCheerEnded();
    void endIntro();
    void endCheer();
    void  draw() override;
    void drawPortrait();
    int32_t getHP();
    Lifebar life;
    
protected:
    
    void insert_AnimationFrame(int x,int y,int w,int h);
   
    
    void changeSource(int32_t index);
    void changePortraitSource(int32_t index);

    static bool _isPlayerTired;

    bool _isLocked=false;
    bool _isVulnerable=false;
    bool _doesPunchLand=false;
    bool _Ko_d=false;
    bool _stoodUp=false;
    bool _hasIntroEnded=false;
    bool _hasCheerEnded=false;

    bool _battleMode=false;
    int _getUpStrength=2;
    int32_t hp=100;
  
    Punch punch_information;
    std::vector<SDL_Rect> sources;
  
    Point positions[3];
    std::unique_ptr<PunchOutTimer> action;
    Image* portrait;
    std::string _name;
    std::string _win_lose_ko;

};
#endif