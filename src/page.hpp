#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cpr/cpr.h>
#include "generator.hpp"


class Page {
    public:
        static std::string ToString(std::string path);
        static bool ValidateURL(std::string url);
        static std::string GenerateFile(std::string url);
        static bool HasHTTP(std::string url);
        static std::string ConvertPath(std::string url);
        static std::string LoadLinkByCode(std::string code);
        static bool CodeExist(std::string code); 
};