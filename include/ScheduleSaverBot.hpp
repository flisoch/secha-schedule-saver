#ifndef SCHEDULESAVER_H
#define SCHEDULESAVER_H

#include "MessageListeners.hpp"
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

class ScheduleSaverBot
{
public:
    void start();
    ScheduleSaverBot(Auth &auth);

private:
    void setEventListeners();

    string token;
    Bot bot;
    Auth &auth;
};

#endif /* SCHEDULESAVER_H */
