#include "Characters.h"

void CharacterManager::GenerateInitialCharacters(int NumOfCharacters, NameGenerator NameGenerator)
{

for(int i = 0; i < NumOfCharacters; i++)
{
    CharacterGivenName.push_back(" ");

    
}

for(int i = 0; i < NumOfCharacters; i++)
{
    CharacterGivenName[i] = NameGenerator.GenerateName(Gen);
}
}