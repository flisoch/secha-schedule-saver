#ifndef MESSAGELISTENERS_H
#define MESSAGELISTENERS_H
#include <nlohmann/json_fwd.hpp>
#pragma once

#include "Auth.hpp"
#include "Requests.hpp"
#include "cpr/cpr.h"
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <tgbot/tgbot.h>

namespace MessageListeners {

inline TgBot::InlineKeyboardMarkup::Ptr
getLinkButtonKeyboard(std::string linkText, std::string link) {
  TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup());
  std::vector<TgBot::InlineKeyboardButton::Ptr> row0;
  TgBot::InlineKeyboardButton::Ptr link_button(
      new TgBot::InlineKeyboardButton());
  link_button->url = link;
  link_button->text = linkText;
  row0.push_back(link_button);
  keyboard->inlineKeyboard.push_back(row0);
  return keyboard;
}

inline TgBot::EventBroadcaster::MessageListener start(TgBot::Bot &bot) {
  return [&bot](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Hi!");
  };
}

inline TgBot::EventBroadcaster::MessageListener auth(TgBot::Bot &bot,
                                                     Auth &auth) {
  return [&bot, &auth](TgBot::Message::Ptr message) {
    auth.waiting_for_tokens.push(std::to_string(message->chat->id));
    auto link = requests::url::google_oauth_code;
    auto keyboard = getLinkButtonKeyboard("Link", link);
    auto reply = bot.getApi().sendMessage(message->chat->id,
                                          "Пройди по ссылке для авторизации",
                                          false, 0, keyboard);
  };
}

inline TgBot::EventBroadcaster::MessageListener schedule(TgBot::Bot &bot,
                                                         Auth &auth) {
  return [&bot, &auth](TgBot::Message::Ptr message) {
    std::string link = /*requests::url::web_server*/
        "http://secha.flisoch.biz:8000/getschedule";
    auto keyboard = getLinkButtonKeyboard("Link", link);
    bot.getApi().sendMessage(message->chat->id,
                             "Посмотреть расписание на сайте", false, 0,
                             keyboard);
  };
}

inline TgBot::EventBroadcaster::MessageListener saveSchedule(TgBot::Bot &bot,
                                                             Auth &auth) {
  return [&bot, &auth](TgBot::Message::Ptr message) {
    if (auth.isAuthorized(message->chat->id)) {
      bot.getApi().sendMessage(message->chat->id,
                               "Загружаю расписание в календарь...");
      Schedule s = Schedule::loadSchedule();
      std::string calendarId = requests::calendar::insertCalendar(
          auth.getToken(message->chat->id), s.summary);
      if (calendarId.empty()) {
        bot.getApi().sendMessage(message->chat->id,
                                 "Google couldn't create a calendar :<( ");
        return;
      }
      auto keyboard =
          getLinkButtonKeyboard("Посмотреть в Google Calendar",
                                "https://calendar.google.com/calendar/");
      bot.getApi().sendMessage(
          message->chat->id,
          "Постепенно загружаю по дням. Уже можешь смотреть!", false, 0,
          keyboard);

      
      requests::calendar::saveSchedule(auth.getToken(message->chat->id), s, calendarId);
      
      bot.getApi().sendMessage(message->chat->id, "Загружено полностью!");

    } else {
      bot.getApi().sendMessage(message->chat->id,
                               "Not authorized. Click /auth");
    }
  };
}

inline TgBot::EventBroadcaster::MessageListener anyMessage(TgBot::Bot &bot) {
  return [&bot](TgBot::Message::Ptr message) {
    std::cout << "User wrote: " << message->text << "\n";
    if (StringTools::startsWith(message->text, "/")) {
      return;
    }
    bot.getApi().sendMessage(message->chat->id,
                             "Your message is: " + message->text);
  };
}
} // namespace MessageListeners

#endif /* MESSAGELISTENERS_H */
