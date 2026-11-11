# pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <random>

#include"NLG/NameGenerator.h"

struct CharacterManager
{
    std::mt19937 Gen;
std::vector<std::string> CharacterGivenName{};
std::vector<uint64_t> CharacterGivenHash{};

std::vector<std::string> CharacterSurname{};
std::vector<uint64_t> CharacterSurnameHash{};

std::vector<std::string> CharacterTitle{};
std::vector<uint64_t> CharacterTitleHash{};

std::vector<std::string> CharacterTrait1{};
std::vector<uint64_t> CharacterTrait1Hash{};

std::vector<uint> CharacterID{};
std::vector<uint> CurrentLocation{};

std::vector<uint16_t> CharacterAge{};
std::vector<uint16_t> CharacterBirthSeason{};
std::vector<char> CharacterGender{};

void GenerateInitialCharacters(int NumOfCharacters, NameGenerator NameGenerator);



};