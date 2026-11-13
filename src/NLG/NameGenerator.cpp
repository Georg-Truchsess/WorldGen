#include "NameGenerator.h" 


std::string NameGenerator::GenerateName()
{
    //Name
    std::string Name;

    //Uniform int distributions for selection and clustering
     std::uniform_int_distribution<int> VowelOrConsenant(1,2);
  
    std::uniform_int_distribution<int> ConsenantClusterSize(1,2);
    std::uniform_int_distribution<int> ConsenantSelection(0,20);
    std::uniform_int_distribution<int> VowelClusterSize(1,2);
    std::uniform_int_distribution<int> VowelSelection(0,4);
  std::uniform_int_distribution<int> SyllableSizer(1,6);
     
    int NameLength = SyllableSizer(Gen);
    int ClusterSize;
    int ChosenConsonant;
    int ChosenVowel;
    
    for(int i = 0; i < NameLength; i++)
    {
       
   
    int ChosenForm = VowelOrConsenant(Gen);
        if(ChosenForm == 1)
        {
            ClusterSize = ConsenantClusterSize(Gen);
                for(int i = 0; i < ClusterSize; i++)
                {
                    ChosenConsonant = ConsenantSelection(Gen);
                     Name.push_back(Consonants[ChosenConsonant]);
                }
            ChosenForm = 2;
        }
        if(ChosenForm == 2)
        {
            ClusterSize = VowelClusterSize(Gen);
            for(int i = 0; i < ClusterSize; i++)
            {
                ChosenVowel = VowelSelection(Gen);
                Name.push_back(Vowels[ChosenVowel]);
            }

            ChosenForm = 1;
        }
    }

    return Name;
}