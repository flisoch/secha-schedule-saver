#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <map>
#include "mongoose.h"
#include "Auth.hpp"

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
