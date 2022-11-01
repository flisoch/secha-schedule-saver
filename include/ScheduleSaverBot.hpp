#ifndef SCHEDULESAVER_H
#define SCHEDULESAVER_H

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <iostream>
#include <tgbot/tgbot.h>
#include "MessageListeners.hpp"

using namespace std;
using namespace TgBot;

class ScheduleSaverBot
{
public:
    void start();
    ScheduleSaverBot();

private:
    void setEventListeners();

    string token;
    Bot bot;
};


#endif /* SCHEDULESAVER_H */
