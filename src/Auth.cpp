#include "Auth.hpp"

bool Auth::isAuthorized(int64_t chatId)
{
    return access_tokens.find(std::to_string(chatId)) != access_tokens.end();
}

std::string Auth::getToken(int64_t chatId)
{
    return access_tokens.at(std::to_string(chatId));
}
