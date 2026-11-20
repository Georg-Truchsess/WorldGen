#include "Characters.h"

void CharacterManager::GenerateInitialCharacters(int NumOfCharacters, NameGenerator NameGenerator)
{
    
CharacterGivenName.resize(50);
CharacterSurname.resize(50);
CurrentLocation.resize(50);
for(int i = 0; i < NumOfCharacters-1; i++)
{
    std::string Name = NameGenerator.GenerateName();
    std::string Surname = NameGenerator.DetermineSurname();
    uint Location = DetermineLocation();
    CharacterGivenName[i] = Name;
    CharacterSurname[i] = Surname;
    CurrentLocation[i] = Location;

}
}

uint CharacterManager::DetermineLocation()
{
    uint Location;

std::uniform_int_distribution<uint> DeterminedTile(0,map.TileID.size()-1);

Location = DeterminedTile(Gen);

if(map.TileHash[5] == map.River || map.TileHash[5] == map.Ocean)
{
   Location = DetermineLocation();
   
}

    return Location;


}