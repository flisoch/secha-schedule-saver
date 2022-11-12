#include "Config.hpp"
#include "ScheduleSaverBot.hpp"
#include "WebServer.hpp"
#include <thread>

int main()
{
    Config &c = Config::instance();
    if (!c.isSetUp()) {
        return -1;
    }

    Auth auth;
    WebServer s(auth);
    ScheduleSaverBot b(auth);
    std::thread t1(&ScheduleSaverBot::start, &b);
    std::thread t2(&WebServer::start, &s);
    t1.join();
    t2.join();
    return 0;
}