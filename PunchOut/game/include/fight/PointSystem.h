#ifndef __PUNCH_OUT_POINTS__
#define __PUNCH_OUT_POINTS__

#include "../../../engine/include/Text.h"
#include <cstdint>
#include <string>
class PointSystem : public Text
{
public:
    PointSystem();
    void draw() override;
    void addPoint(int point);
    std::string getPoints_to_string();
    int32_t getPoints();
private:
    int32_t points=0;
};

#endif