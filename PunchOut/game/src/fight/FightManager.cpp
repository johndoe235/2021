#include "../../include/fight/FightManager.h"
#include "../../include/fight/Ring.h"
#include "../../include/boxers/Boxer.h"
#include "../../include/Resources.h"
#include "../../include/boxers/lilMac.h"
#include "../../include/boxers/glassJoe.h"

#include "../../include/fight/Ring.h"
#include "../../include/fight/Referee.h"
#include "../../include/fight/Round.h"
#include "../../include/fight/PointSystem.h"
void FightManager::init(lilMac*& Player)
{
    Player=new lilMac();
    player=Player;
    
    opponent=new glassJoe();
    round=new Round();
    ring=new Ring();
    points=new PointSystem();
    mario=new Referee();

    playerName=new Text();
    opponentName=new Text();
    player_win_lose_ko=new Text();;
    opponent_win_lose_ko=new Text();
    versus=new Text();
    instructions=new Text();
    trainer=new Text();

    ring->setTexture(PUNCH_OUT_TEXTURES::RING_RING_BACKGROUND);
    mario->setTexture(PUNCH_OUT_TEXTURES::FIGHT_REFEREE_TEXTURE);
    player->setTexture(PUNCH_OUT_TEXTURES::BOXER_LIL_MAC_TEXTURE);
    opponent->setTexture(PUNCH_OUT_TEXTURES::BOXER_GLASS_JOE_TEXTURE);

    player->init();
    opponent->init();
    mario->init();

   
    points->setPosition(622,69,26,24);
    player->setMaxHearts(20);

    player->Lock();

    opponentIntroActivated=false;
    start_only_once=false;
    _cheer_only_once=false;
    _FIGHT_OVER=false;
    currentState=FIGHT_STATE::CORNER;


    playerName->setPosition(30,560,25,25);
    opponentName->setPosition(600,70,25,25);
    versus->setPosition(380,300,25,25);
    instructions->setPosition(580,600,25,25);
    trainer->setPosition(0,150,20,20);
    player_win_lose_ko->setPosition(30,320,25,25);
    opponent_win_lose_ko->setPosition(600,320,25,25);

    playerName->write(player->boxerName());
    opponentName->write(opponent->boxerName());

    player_win_lose_ko->write(player->win_lose_ko_());
    opponent_win_lose_ko->write(opponent->win_lose_ko_());

    versus->write("VS.");
    instructions->write("PUSH ENTER");
    trainer->write("\"Punch\nby pressing\nZ or X Mac!\nDon't forget to\nmove your head\nwith the arrow keys!\"");
   
    
}

 void FightManager::Enter_pressed()
 {
     if(currentState==FIGHT_STATE::FIGHT)
     {
                //mac super attack
     }
     else if(currentState==FIGHT_STATE::CORNER)
     {
         if(round->currentRound()==3)
             currentState=FIGHT_STATE::DECISION;
         else
            currentState=FIGHT_STATE::INTRODUCTION;

        player->teleportTO_introPosition();
        opponent->teleportTO_introPosition();
        mario->teleportTO_introPosition();

     }
 }
void FightManager::fightNight()
{
    if(currentState==FIGHT_STATE::INTRODUCTION)
    {
        introduction();
    }
    else if(currentState==FIGHT_STATE::PRE_FIGHT)
    {
        preFight();
    }
    else if(currentState==FIGHT_STATE::FIGHT)
    {
        fight();
    }
    
    else if(currentState==FIGHT_STATE::CORNER)
    {
        corner();
    }
    else if(currentState==FIGHT_STATE::KO)
    {
        KO();
    }
    else if(currentState==FIGHT_STATE::DECISION)
    {
        decision();
    }
    
}
void FightManager::introduction()
{
    if(!opponentIntroActivated)
    {
        opponent->IntroAnimation();
        opponentIntroActivated=true;
    }

    if(opponent->hasIntroEnded())
    {
        currentState=FIGHT_STATE::PRE_FIGHT;
        opponent->moveToNeutralPosition();
        
    }


    opponent->update();
  
    
    
}
void FightManager::preFight()
{
    if(opponent->isInNeutralPosition())
    {
        GameObject::playSound(PUNCH_OUT_SOUND::BELL_RING);
        mario->sayFight();
        opponent->moveToBattlePosition();
        player->moveToBattlePosition();
        currentState=FIGHT_STATE::FIGHT;
        GameObject::playMusic(PUNCH_OUT_SOUND::FIGHT_THEME);
        round->roundStart();
        player->Unlock();
    }
    opponent->update();

}
void FightManager::fight()
{
    
    opponent->update(); 
    player->update(); 
    round->update();
    mario->update();


    if(opponent->hasPunchLanded())
    {
        player->handleIncomingPunch(opponent->punchInformation());
    }
    if(player->hasPunchLanded())
    {
        if(opponent->handleIncomingPunch(player->punchInformation()))
        {
            points->addPoint(player->punchInformation().points);
        }
        else
        player->decreaseHearts(1);
    }

    if(round->hasRoundEnded())
    {
        currentState=FIGHT_STATE::CORNER;
        GameObject::playSound(PUNCH_OUT_SOUND::BELL_RING);
        GameObject::pauseMusic();
    }



    if(player->isKO_D() || opponent->isKO_D())
    {
        currentState=FIGHT_STATE::KO;


        mario->walkIn();
        if(player->isKO_D())
        opponent->moveToNeutralPosition();
        if(opponent->isKO_D())
           player->moveToNeutralPosition();
        ///pause timers;
    }
    
}


void FightManager::corner()
{
    player->updatePortrait();
    opponent->updatePortrait();

}

void FightManager::KO()
{
   
    if(mario->getXposition()<=640)
    {
        
        mario->count(player->isKO_D());
        
    }

    if(mario->finishedCount())
    {
        if(!_cheer_only_once)
        {
        GameObject::pauseMusic();
        GameObject::playSound(PUNCH_OUT_SOUND::CROWD_CHEER_CHUNK);
            if(player->isKO_D())
                opponent->cheer();

            else if(opponent->isKO_D())
            player->cheer();

        _cheer_only_once=true;
        }
    }

    if(player->isKO_D())
    {
        if(opponent->hasCheerEnded())
            _FIGHT_OVER=true;
    }
    else if(opponent->isKO_D())
    {
        if(player->hasCheerEnded())
        {
            _FIGHT_OVER=true;
        }
    }
    player->update();
    opponent->update();
    mario->update();

}

void FightManager::decision()
{
    bool is_player_the_winner=(points->getPoints()==5000);
    
    mario->decide(is_player_the_winner);
   


    if(mario->hasAnnouncedDecision() && !_cheer_only_once)
    {
     _cheer_only_once=true;  
     GameObject::playSound(PUNCH_OUT_SOUND::CROWD_CHEER_CHUNK);
       if(is_player_the_winner)
            player->cheer();
        else
        opponent->cheer();
        
    }

    if(is_player_the_winner)
    {
        if(player->hasCheerEnded())
            _FIGHT_OVER=true;
    }
    else 
    {
        if(opponent->hasCheerEnded())
        {
            _FIGHT_OVER=true;
        }
    }

    player->update();
    opponent->update();
    mario->update();

}
void FightManager::draw()
{
    if(currentState!=FIGHT_STATE::CORNER)
    {
    ring->draw();
    round->draw();
    points->draw();

    
    opponent->draw();
    player->draw();
 
    mario->draw();
    }
    else
    {
        player->drawPortrait();
        opponent->drawPortrait();
        playerName->draw();
        opponentName->draw();
        player_win_lose_ko->draw();
        opponent_win_lose_ko->draw();
        versus->draw();
        instructions->draw();
        trainer->draw();
    }
  
}
bool FightManager::changeToMenuState()
{
    if(_FIGHT_OVER)
    {
        free_allocated_memory();

        _FIGHT_OVER=false;
        return true;
    }
    return false;
}

void FightManager::free_allocated_memory()
{
    if(!opponent)
    {
    delete opponent;
    opponent=0;
    }
    if(!player)
    {
    delete player;
    player=0;
    }
    if(!round)
    {
    delete round;
    round=0;
    }
    if(!ring)
    {
    delete ring;
    ring=0;
    }
    if(!points)
    {
    delete points;
    points=nullptr;
    }
    if(!playerName)
    {
    delete playerName;
    playerName=nullptr;
    }
    if(!opponentName)
    {
    delete opponentName;
    opponentName=nullptr;
    }
    if(!player_win_lose_ko)
    {
    delete player_win_lose_ko;
    player_win_lose_ko=nullptr;
    }
    if(!opponent_win_lose_ko)
    {
    delete opponent_win_lose_ko;
    opponent_win_lose_ko=nullptr;
    }
    if(!versus)
    {
    delete versus;
    versus=nullptr;
    }
    if(!instructions)
    {
    delete instructions;
    instructions=nullptr;
    }
    if(!trainer)
    {
        delete trainer;
        trainer=nullptr;
    }
}