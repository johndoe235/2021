#ifndef __JOE_IMAGE__
#define __JOE_IMAGE__

/* C system includes */

/* C++ system includes */

/* Third-party includes */

/* Own includes */
#include "GameObject.h"
/* Forward Declaration */

///




class Image: public GameObject
{
    public:
    void makeInvisible();
    void makeVisible();
    void draw() override;


    private:
    bool _isVisible=true;
};



#endif