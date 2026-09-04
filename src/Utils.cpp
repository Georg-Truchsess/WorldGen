#include "Utils.h"
#include <iostream>
#include<cmath>
#include<algorithm>
uint16_t Distance(uint16_t TilePosX1, uint16_t TilePosY1, uint16_t TilePosX2, uint16_t TilePosY2)
{
    int X = std::max(TilePosX1, TilePosX2) - std::min(TilePosX1, TilePosX2);
    int Y = std::max(TilePosY1, TilePosY2) - std::min(TilePosY1, TilePosY2);
    // Uses euclidean distance formula and then divides by thirty, given that each tile is thirty pixels by 30 pixels
    return std::sqrt((X * X) + (Y * Y))/30;

}