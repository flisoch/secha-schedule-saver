#ifndef GOOGLECONNECTOR_H
#define GOOGLECONNECTOR_H

#include <string>
#include <map>
#include <deque>

class Auth
{

public:
    typedef std::string ChatdId;
    bool isAuthorized(int64_t chatId);
    std::string getToken(int64_t chatId);
    void authRequest(int64_t chatId);

    std::map<std::string, std::string> access_tokens;
    std::deque<ChatdId> waiting_for_tokens;
};

#endif /* GOOGLECONNECTOR_H */
