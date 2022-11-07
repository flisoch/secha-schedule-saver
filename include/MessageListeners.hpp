#ifndef MESSAGELISTENERS_H
#define MESSAGELISTENERS_H
#pragma once

#include <iostream>
#include <fstream>
#include <tgbot/tgbot.h>
#include <boost/tokenizer.hpp>
#include "Auth.hpp"
#include "cpr/cpr.h"
#include "Requests.hpp"

namespace MessageListeners
{

    inline TgBot::EventBroadcaster::MessageListener start(TgBot::Bot &bot)
    {
        return [&bot](TgBot::Message::Ptr message)
        { bot.getApi().sendMessage(message->chat->id, "Hi!"); };
    }

    inline TgBot::EventBroadcaster::MessageListener auth(TgBot::Bot &bot, Auth &auth)
    {
        return [&bot, &auth](TgBot::Message::Ptr message)
        {
            auth.waiting_for_tokens.push(std::to_string(message->chat->id));
            bot.getApi().sendMessage(message->chat->id, requests::url::google_oauth_code);
        };
    }

    inline TgBot::EventBroadcaster::MessageListener schedule(TgBot::Bot &bot, Auth &auth)
    {
        return [&bot, &auth](TgBot::Message::Ptr message)
        {
            std::string schedule = requests::calendar::schedule(std::to_string(message->chat->id));
            bot.getApi().sendMessage(message->chat->id, schedule);
        };
    }

    inline TgBot::EventBroadcaster::MessageListener saveSchedule(TgBot::Bot &bot, Auth &auth)
    {
        return [&bot, &auth](TgBot::Message::Ptr message)
        {
            if (auth.isAuthorized(message->chat->id))
            {
                Schedule s = Schedule::loadSchedule();
                requests::calendar::saveSchedule(auth.getToken(message->chat->id), s);
                bot.getApi().sendMessage(message->chat->id, "https://calendar.google.com/calendar/");
            }
            else
            {
                bot.getApi().sendMessage(message->chat->id, "Not authorized. Click /auth");
            }
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
