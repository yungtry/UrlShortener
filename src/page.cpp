#include "page.hpp"

std::string Page::ToString(std::string path) {
    std::ifstream t(path);
    std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    return str;
}

bool Page::ValidateURL(std::string url) {
    auto r = cpr::Get(url);
    if (r.status_code != 0) {
        return true;
    }
    else {
        return false;
    }
}

std::string Page::GenerateFile(std::string url) {
    std::string code = Generate::random_string(6);
    std::cout << "./urls/"+code+".txt" << std::endl;
    if(!std::filesystem::exists("./urls/"+code+".txt")){
        std::ofstream outfile;
        outfile.open("./urls/"+code+".txt", std::ios_base::app);
        outfile << url;
        std::string page = Page::ToString("html/shorten.html");
        while (page.find("[INSERTCODE]") != std::string::npos)
        page.replace(page.find("[INSERTCODE]"), 12, code);
        while (page.find("[INSERTURL]") != std::string::npos)
        page.replace(page.find("[INSERTURL]"), 11, code);
        return page.c_str();
    }
    else {
        std::cout << "Duplicate" << std::endl;
        Page::GenerateFile(url);
    }
}

std::string Page::ConvertPath(std::string url) {
    std::string mountpoint = url.c_str();
    std::string code = mountpoint.erase(0,1);
    return code;
}

bool Page::HasHTTP(std::string url) {
    if (url.rfind("http://", 0) == 0 || url.rfind("https://", 0) == 0) {
        return true;
    }
    else {
        return false;
    }
}

std::string Page::LoadLinkByCode(std::string code) {
    return Page::ToString("./urls/"+code+".txt");
}