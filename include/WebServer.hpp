#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Auth.hpp"
#include "mongoose.h"
#include <map>

class WebServer
{
public:
    WebServer(Auth &auth);
    void start();

private:
    struct mg_mgr mgr;
    Auth &auth;
};

#endif /* WEBSERVER_H */
