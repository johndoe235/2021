#include "../include/Game.h"
#include "../../engine/include/Window.h"
#include "../../engine/include/Renderer.h"
#include "../../engine/include/Text.h"
#include "../include/Resources.h"
void Game::onUserCreate()
{

   
   GameObject::loadTexture(PUNCH_OUT_TEXTURES::BOXER_LIL_MAC_TEXTURE,"../res/lilMac.png");
   GameObject::loadTexture(PUNCH_OUT_TEXTURES::BOXER_GLASS_JOE_TEXTURE,"../res/glassJoe.png");
   GameObject::loadTexture(PUNCH_OUT_TEXTURES::FIGHT_REFEREE_TEXTURE,"../res/referee.png");

   GameObject::loadTexture(PUNCH_OUT_TEXTURES::RING_RING_BACKGROUND,"../res/ring.png");

   GameObject::loadTexture(PUNCH_OUT_TEXTURES::MENU_TITLE_SCREEN,"../res/title/title_screen.png");
   GameObject::loadTexture(PUNCH_OUT_TEXTURES::MENU_NEW_GAME,"../res/title/new_game.jpg");
   GameObject::loadTexture(PUNCH_OUT_TEXTURES::MENU_CONTINUE,"../res/title/continue.jpg");
   GameObject::loadTexture(PUNCH_OUT_TEXTURES::MENU_GLOVE,"../res/title/glove.jpg");
   
   
   GameObject::loadMusic(PUNCH_OUT_SOUND::GLASS_JOE_THEME,"../res/sound/glassjoe_theme.wav");
   GameObject::loadMusic(PUNCH_OUT_SOUND::FIGHT_THEME,"../res/sound/fight_theme.wav");

   
   
   GameObject::loadSound(PUNCH_OUT_SOUND::CROWD_CHEER_CHUNK,"../res/sound/crowd_cheering.wav"); 
   GameObject::loadSound(PUNCH_OUT_SOUND::MAC_DODGE_CHUNK,"../res/sound/mac_dodge.wav");
   //ameObject::loadSound(PUNCH_OUT_SOUND::MAC_PUNCH_BLOCKED_CHUNK,"..res/sound/mac_block.wav");
   GameObject::loadSound(PUNCH_OUT_SOUND::MAC_PUNCH_BLOCKED_CHUNK,"../res/sound/mac_punch_blocked.wav");
   GameObject::loadSound(PUNCH_OUT_SOUND::MAC_PUNCH_CHUNK,"../res/sound/mac_punch.wav");
   GameObject::loadSound(PUNCH_OUT_SOUND::OPPONENT_PUNCH,"../res/sound/opponent_punch.wav");
   GameObject::loadSound(PUNCH_OUT_SOUND::BELL_RING,"../res/sound/bell.wav");
 


   Text::loadEngineFont("../res/font/punchOutFont.ttf",30);

   menu.load();


   
    
}
void Game::onUserUpdate()
{
    
  switch(currentState)
  {
    case GAME_STATES::MENU:
        onMenuStateUpdate();
    break;
    case GAME_STATES::FIGHT:
        onFightStateUpdate();
    break;
    case GAME_STATES::CREDITS:
    break;

  }
  

    
}
void Game::onUserQuit()
{    

    Text::freeEngineFont();
}

void Game::onMenuStateUpdate()
{
    if(menu.clickedButton()==Button_ID::NEW_GAME)
    {
        currentState=GAME_STATES::FIGHT;
        fightMngr.init(mac);
    }

    menu.draw();
   
}
void Game::onFightStateUpdate()
{
    
    

    fightMngr.fightNight();
    fightMngr.draw();

    if(fightMngr.changeToMenuState())
    currentState=GAME_STATES::MENU;

}