#ifndef GOOGLECONNECTOR_H
#define GOOGLECONNECTOR_H

#include <string>
#include <map>
#include <queue>

class Auth
{

public:
    typedef std::string ChatdId;
    bool isAuthorized(int64_t chatId);
    std::string getToken(int64_t chatId);


    std::map<std::string, std::string> access_tokens;
    std::queue<ChatdId> waiting_for_tokens;
};

#endif /* GOOGLECONNECTOR_H */
