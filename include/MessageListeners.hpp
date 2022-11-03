#ifndef MESSAGELISTENERS_H
#define MESSAGELISTENERS_H
#pragma once

#include <iostream>
#include <tgbot/tgbot.h>
#include "Auth.hpp"
#include "cpr/cpr.h"

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
        {
            Auth auth;
            long status = auth.setCurrentChat(std::to_string(message->chat->id));
            if (status == 200)
            {
                bot.getApi().sendMessage(message->chat->id, "https://accounts.google.com/o/oauth2/auth?client_id=227386243715-g04tg86v3228v9u6ng697c678or5obtn.apps.googleusercontent.com&redirect_uri=http://localhost:8000/authorize&scope=https://www.googleapis.com/auth/calendar.app.created&response_type=code");
            }
            else {
                bot.getApi().sendMessage(message->chat->id, "Error. Cannot authenticate");
            }
        };
    }

    inline TgBot::EventBroadcaster::MessageListener schedule(TgBot::Bot &bot)
    {
        return [&bot](TgBot::Message::Ptr message)
        {
            Auth auth;
            std::string schedule = auth.schedule(std::to_string(message->chat->id));
            bot.getApi().sendMessage(message->chat->id, schedule);
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
