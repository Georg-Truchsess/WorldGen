#pragma once

#include<string>
#include<random>

struct NameGenerator
{
    std::mt19937 Gen;
 char Consonants[21] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};
 char Vowels[5] = {'a','e','i','o','u'};

std::string GenerateName();

};