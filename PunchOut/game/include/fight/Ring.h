#ifndef __PUNCH_OUT_RING__
#define __PUNCH_OUT_RING__

#include "../../../engine/include/GameObject.h"
#include "../timers/PunchOutTimer.h"

#include <vector>
#include<memory>







class Ring : public GameObject
{
public:
        Ring();
        ~Ring();
        void startRound();
        bool hasRoundEnded();


        
private:
std::unique_ptr<PunchOutTimer> action;
};


#endif
