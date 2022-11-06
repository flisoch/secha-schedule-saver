#include <thread>
#include "ScheduleSaverBot.hpp"
#include "WebServer.hpp"

int main()
{
    Auth auth;
    WebServer s(auth);
    ScheduleSaverBot b(auth);
    std::thread t1(&ScheduleSaverBot::start, &b);
    std::thread t2(&WebServer::start, &s);
    t1.join();
    t2.join();
    return 0;
}