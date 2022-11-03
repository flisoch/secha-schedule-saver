#include <iostream>
#include "Auth.hpp"
#include "cpr/cpr.h"
#include <nlohmann/json.hpp>

std::string Auth::getToken(std::string code)
{
    nlohmann::json body;
    std::string token;

    body["code"] = code;
    body["client_id"] = client_id;
    body["client_secret"] = client_secret;
    body["grant_type"] = grant_type;
    body["redirect_uri"] = redirect_uri;

    cpr::Response r = cpr::Post(
        cpr::Url{google_oauth_url},
        cpr::Body{body.dump()},
        cpr::Header{{"Content-Type", "application/json"}});
    nlohmann::json json_response = nlohmann::json::parse(r.text);
    if (json_response.contains("access_token"))
    {
        token = json_response["access_token"].dump();
        std::cout << token << std::endl;
    }
    else
    {
        std::cout << r.text << std::endl;
    }
    return token;
}

long Auth::setCurrentChat(std::string chatId)
{
    nlohmann::json body;
    body["chat_id"] = chatId;
    cpr::Response r = cpr::Post(
        cpr::Url{auth_server_uri + "/current"},
        cpr::Body{body.dump()},
        cpr::Header{{"Content-Type", "application/json"}});
    return r.status_code;
}

std::string Auth::schedule(std::string chatId)
{

    nlohmann::json body;
    body["chat_id"] = chatId;
    cpr::Response r = cpr::Post(
        cpr::Url{auth_server_uri + "/schedule"},
        cpr::Body{body.dump()},
        cpr::Header{{"Content-Type", "application/json"}});
    std::cout << r.text << std::endl;
    return r.text;
}
