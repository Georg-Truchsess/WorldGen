#include "Characters.h"

void CharacterManager::GenerateInitialCharacters(int NumOfCharacters, NameGenerator NameGenerator)
{

for(int i = 0; i < NumOfCharacters-1; i++)
{
    std::string Name = NameGenerator.GenerateName();
    std::string Surname = NameGenerator.DetermineSurname();
    uint Location = DetermineLocation(map);
    CharacterGivenName.push_back(Name);
    CharacterSurname.push_back(Surname);
    CurrentLocation.push_back(Location);

}
}

uint CharacterManager::DetermineLocation(TileMap map)
{
    uint Location;

std::uniform_int_distribution<int> DeterminedTile(0,map.TileID.size()-1);

Location = DeterminedTile(Gen);

if(map.TileHash[Location] == map.River || map.TileHash[Location] == map.Ocean)
{
    DetermineLocation(map);
}
else
{
    return Location;
}

}