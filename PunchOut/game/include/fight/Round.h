#ifndef __PUNCH_OUT_ROUND__
#define __PUNCH_OUT_ROUND__


#include "../timers/RoundTimers.h"
#include <memory>

class Renderer;
class Text;

enum class ROUND_TIMERS_ID
{
        ROUND_TIMER
};
class Round
{
public:
    Round();
    ~Round();
    bool hasRoundEnded();
    void roundStart();
    void roundPause();
    void update();
    int currentRound();
    void draw();

private:
std::unique_ptr<RoundTimer>  round_timer;
Text* visual_clock=nullptr;
Text* round_num=nullptr;
int round=0;
};


#endif
