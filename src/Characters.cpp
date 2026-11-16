#include "Characters.h"

void CharacterManager::GenerateInitialCharacters(int NumOfCharacters, NameGenerator NameGenerator)
{

for(int i = 0; i < NumOfCharacters-1; i++)
{
    std::string Name = NameGenerator.GenerateName();
    std::string Surname = NameGenerator.DetermineSurname();
    CharacterGivenName.push_back(Name);
    CharacterSurname.push_back(Surname);

}
}