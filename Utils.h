#pragma once

#include "./json.hpp"

#include <iomanip>
#include <string>
#include <fstream>


namespace utils
{

    void writeFile(std::string path, nlohmann::json text);
    void writeJsonFile(std::string path, nlohmann::json text);
    std::string readFile(std::string);
    nlohmann::json readJsonFile(std::string);

};

