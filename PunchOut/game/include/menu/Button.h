#ifndef __PUNCH_OUT_MENU_BUTTON__
#define __PUNCH_OUT_MENU_BUTTON__

#include "../../../engine/include/GameObject.h"
enum class Button_ID
{
    NONE,
    NEW_GAME,
    CONTINUE,
    HIGH_SCORE
};


class Button : public GameObject
{
public:
    Button(Button_ID);
    ~Button();
    bool isClicked();
    bool isSelected();
    const Button_ID id;
private:
    bool _clicked;
    bool _selected;
    bool locked;
    bool visible;
    
};

#endif