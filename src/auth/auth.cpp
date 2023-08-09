#define CURL_STATICLIB
#include "../clicker/clicker.h"
#include <iostream>
#include <string>
#include "curl.h"
#include "json.h"
#include "xorstr.h"

bool vars::auth::authenticate() {
    vars::auth::user = vars::auth::ze();
    Json::Value d;
    
    //HW_PROFILE_INFO hwProfileInfo;
    d["hwid"] = vars::auth::hwid;
    std::string dStr = d.toStyledString();
    
    std::string response;
    

    std::vector<char>* buf = vars::auth::getf(dStr, "hwid");
    


    for (const auto& i : *buf) {
        response.push_back(i);
    }
    delete buf;


    if (response.empty()) {
        return false;
    }
    
    else if (response == "nigger" + vars::auth::version + vars::auth::hwid) {
        return true;
    }
    else {
        return false;
    }
}

size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<char>* vars::auth::getf(std::string params, std::string path) {
    std::string* response = new std::string();
    std::vector<char>* buf = new std::vector<char>();
    CURL* curl = curl_easy_init();
    CURLcode res;

    if (curl) {
        std::string url = xorstr("https://db.sparked.network/") + path;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            for (const auto& i : *response)
                buf->push_back(i);

            delete response;
        }

    }
    curl_easy_cleanup(curl);

    return buf;
}
