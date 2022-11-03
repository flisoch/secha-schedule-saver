#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <map>
#include "mongoose.h"
#include "Auth.hpp"

class AuthServer {
public:
    AuthServer();
private:
    void init();

    struct mg_mgr mgr;
    Auth auth;
};

#endif /* WEBSERVER_H */
