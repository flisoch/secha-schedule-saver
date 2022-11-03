#ifndef GOOGLECONNECTOR_H
#define GOOGLECONNECTOR_H

#include <string>
#include <map>

class Auth
{

public:
    std::string getToken(std::string code);
    std::string schedule(std::string access_token);
    long setCurrentChat(std::string chatId);
    const std::string client_id = "227386243715-g04tg86v3228v9u6ng697c678or5obtn.apps.googleusercontent.com";
    const std::string client_secret = "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";
    const std::string grant_type = "authorization_code";
    const std::string scopes = "https://www.googleapis.com/auth/calendar.app.created";
    const std::string google_oauth_url = "https://accounts.google.com/o/oauth2/token";
    const std::string auth_server_uri = "http://localhost:8000";
    const std::string redirect_uri = auth_server_uri + "/authorize";

    std::map<std::string, std::string> access_tokens;
    std::string current_chat_id;
};

#endif /* GOOGLECONNECTOR_H */
