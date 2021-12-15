#ifndef __PUNCH_OUT_LIFE_BAR__
#define __PUNCH_OUT_LIFE_BAR__

#include "../../../engine/include/GameObject.h"

class Lifebar : public GameObject
{
    public:
    Lifebar();
    ~Lifebar();
    void update(int health);
    void draw() override;
    private:
    int current_health=100;
    float amount_to_take=0;
    float current_visual_health;
};


#endif