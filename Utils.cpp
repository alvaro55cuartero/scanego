#include "Utils.h"


namespace utils {

    std::string readFile(std::string path) {
        std::string line;
        std::string out;
        std::ifstream file(path);
        if (file.is_open())
        {
            while (std::getline(file, line))
            {
                out.append(line);
            }
            file.close();
        }
        else return "";

        return out;
    }

    nlohmann::json readJsonFile(std::string path) {
        return nlohmann::json::parse(readFile(path));
    }


    void writeFile(std::string path, nlohmann::json text) {
        std::ofstream file;

        file.open(path);
        file << text;
        file.close();
    }

    void writeJsonFile(std::string path, nlohmann::json text) {
        std::ofstream file;

        file.open(path);
        file << std::setw(4) << text;
        file.close();
    }
}