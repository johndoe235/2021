#ifndef __PUNCH_OUT_GAME__
#define __PUNCH_OUT_GAME__
#include "../../engine/include/GameMakerEngine.h"
#include "../../engine/include/Window.h"
#include "boxers/lilMac.h"
#include "boxers/glassJoe.h"
#include "menu/Menu.h"
#include "fight/FightManager.h"

enum class GAME_STATES
{
    MENU,
    FIGHT,
    CREDITS,
};
class Game : public GameMakerEngine
{
    public:
    

    private:
    //engine functions
    void onUserCreate() override;
    void onUserUpdate() override;
    void handleInput() override;
    void onUserQuit() override;
     
    //game specific functions
    void onMenuStateUpdate();
    void onFightStateUpdate();
    

    //Objects
    Menu menu;
    FightManager fightMngr;
    lilMac* mac;

   
    ////variables that make stuff work the way it should
    GAME_STATES currentState=GAME_STATES::MENU;
};
#endif