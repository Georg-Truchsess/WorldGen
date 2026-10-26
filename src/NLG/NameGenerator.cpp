#include "NameGenerator.h" 


std::string NameGenerator::GenerateName(std::mt19937 Gen)
{
    //Name
    std::string Name;

    //Uniform int distributions for selection and clustering
    std::uniform_int_distribution<int> VowelOrConsenant(1,2);
    std::uniform_int_distribution<int> SyllableSizer(1,6);
    std::uniform_int_distribution<int> ConsenantClusterSize(1,4);
    std::uniform_int_distribution<int> ConsenantSelection(0,23);
    std::uniform_int_distribution<int> VowelClusterSize(1,2);
    std::uniform_int_distribution<int> VowelSelection(0,4);


    int NameLength = SyllableSizer(Gen);
    int ChosenForm = VowelOrConsenant(Gen);
    int ClusterSize;
    int ChosenConsonant;
    int ChosenVowel;
    for(int i = 0; i < NameLength; i++)
    {
        if(ChosenForm = 1)
        {
            ClusterSize = ConsenantClusterSize(Gen);
                for(int i = 0; i < ClusterSize; i++)
                {
                    ChosenConsonant = ConsenantSelection(Gen);
                     Name.push_back(Consonants[ChosenConsonant]);
                }
            ChosenForm = 2;
        }
        if(ChosenForm = 2)
        {
            ClusterSize = VowelClusterSize(Gen);
            for(int i = 0; i < ClusterSize; i++)
            {
                ChosenVowel = VowelSelection(Gen);
                Name.push_back(Vowels[ChosenVowel]);
            }
        }
    }

    return Name;
}