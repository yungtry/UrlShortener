#include "config.h"
#include "defaults.h"

#include <iostream>
#include <string>
#include <future>
#include <httplib.h>

#include "page.hpp"

httplib::Server svr;

int main(int argc, char const *argv[])
{
    std::cout << "Running server on port " << config_port << std::endl;

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content(Page::ToString("html/index.html").c_str(), "text/html");
    });

    svr.Post("/shorten", [](const httplib::Request& req, httplib::Response& res) {
       if (Page::ValidateURL(req.get_param_value("url"))) {
            auto code = std::async(Page::GenerateFile, req.get_param_value("url"));
            std::string content = code.get();
            res.set_content(content, "text/html");

       }
        else {
            //Wrong url
            std::cerr << "Parsing failed: " << req.get_param_value("url") << std::endl;
            res.set_content("Wrong url!", "text/html");
        }
    });

    svr.set_error_handler([](const httplib::Request& req, httplib::Response& res) {
        
        std::string code = Page::ConvertPath(req.path);

        if(std::filesystem::exists("./urls/"+code+".txt") && (Page::HasHTTP(Page::LoadLinkByCode(code)))) {
            res.set_redirect(Page::LoadLinkByCode(code).c_str());
        }
        else if (std::filesystem::exists("./urls/"+code+".txt") && (!Page::HasHTTP(Page::LoadLinkByCode(code)))) {
                std::string redirect = "https://"+Page::LoadLinkByCode(code);
                res.set_redirect(redirect.c_str());
        }
        else {
            //404
            res.set_header("status", "404");
            res.set_content("404", "text/plain");
        } 
        
    });

    auto ret = svr.set_mount_point("/", "./static");
    if (!ret) {
        // The specified base directory doesn't exist...
    }
    svr.listen(config_host, config_port);
    
}