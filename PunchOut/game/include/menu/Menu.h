#ifndef __PUNCH_OUT_MENU_SCREEN__
#define __PUNCH_OUT_MENU_SCREEN__

class Texture;
class Renderer;
class Button;
#include "../../../engine/include/GameObject.h"
#include <vector>
#include "Button.h"


class Menu : public GameObject
{
public:
    Menu();
    ~Menu();
    void clickSelectedButton();
    void load();
    void nextButton();
    void previousButton();
    void draw() override;
    //void update();

    Button_ID clickedButton();


private:
   void moveGlove();
bool lock;
std::vector<Texture*> textures;
std::vector<Button> buttons;
Button_ID buttonClickedID;
Button _select;
int selectedB_index;

};



#endif