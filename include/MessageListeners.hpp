#ifndef MESSAGELISTENERS_H
#define MESSAGELISTENERS_H
#pragma once

#include <iostream>
#include <tgbot/tgbot.h>
#include "CalendarConnector.hpp"

namespace MessageListeners
{
    inline TgBot::EventBroadcaster::MessageListener start(TgBot::Bot &bot)
    {
        return [&bot](TgBot::Message::Ptr message)
        { bot.getApi().sendMessage(message->chat->id, "Hi!"); };
    }

    inline TgBot::EventBroadcaster::MessageListener auth(TgBot::Bot &bot)
    {
        return [&bot](TgBot::Message::Ptr message)
        { bot.getApi().sendMessage(message->chat->id, "Not supported yet!"); };
    }

    inline TgBot::EventBroadcaster::MessageListener schedule(TgBot::Bot &bot)
    {
        return [&bot](TgBot::Message::Ptr message)
        {
            callPythonScript();
            bot.getApi().sendMessage(message->chat->id, "Not supported yet!"); 
        };
    }

    inline TgBot::EventBroadcaster::MessageListener saveSchedule(TgBot::Bot &bot)
    {
        return [&bot](TgBot::Message::Ptr message)
        {

            bot.getApi().sendMessage(message->chat->id, "Not supported yet!");
        };
    }

    inline TgBot::EventBroadcaster::MessageListener anyMessage(TgBot::Bot &bot)
    {
        return [&bot](TgBot::Message::Ptr message)
        {
        std::cout << "User wrote: " << message->text << "\n";
        if (StringTools::startsWith(message->text, "/")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text); };
    }
}


#endif /* MESSAGELISTENERS_H */
