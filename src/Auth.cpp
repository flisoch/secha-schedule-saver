#include "Auth.hpp"
#include <algorithm>
#include <string>

bool Auth::isAuthorized(int64_t chatId)
{
    return access_tokens.find(std::to_string(chatId)) != access_tokens.end();
}

std::string Auth::getToken(int64_t chatId)
{
    return access_tokens.at(std::to_string(chatId));
}

void Auth::authRequest(int64_t chatId)
{
    std::string chat = std::to_string(chatId);
    auto it = std::find_if(waiting_for_tokens.begin(), waiting_for_tokens.end(),
                           [chat](const std::string &i) { return chat == i; });
    if (it != waiting_for_tokens.end()) {
        waiting_for_tokens.erase(it);
    }
    waiting_for_tokens.push_back(chat);
}
