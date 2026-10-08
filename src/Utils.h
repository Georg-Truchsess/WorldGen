#pragma once

#include<iostream>
#include <cstdint>
#include <vector>

// used to find distance between tiles in number of tiles
uint16_t Distance(uint16_t TilePosX1, uint16_t TilePosY1, uint16_t TilePosX2, uint16_t TilePosY2);

template <typename T>
void PrintVector(uint16_t NumX, const std::vector<T>& vec )
{
    int CurrentWidth = 0;
  
  int counter = 0;
for(const auto& item : vec)
{

    if (CurrentWidth < NumX)
    {
        
        //std::cout << static_cast<int>(vec[counter]) << " ";
        std::cout << item << " "; 
   
    }
    if (CurrentWidth > NumX)
    {
        
        std::cout << " " << std::endl;
        CurrentWidth = 0;
    }
    counter++;
}

}

