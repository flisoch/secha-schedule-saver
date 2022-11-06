#include "ScheduleSaverBot.hpp"

ScheduleSaverBot::ScheduleSaverBot(Auth& auth)
    : token{getenv("SECHA_BOT_TOKEN")},
      bot{token}, 
      auth{auth}
{
    setEventListeners();
}

void ScheduleSaverBot::setEventListeners()
{
    bot.getEvents().onCommand("start", MessageListeners::start(bot));
    bot.getEvents().onCommand("auth", MessageListeners::auth(bot, auth));
    bot.getEvents().onCommand("schedule", MessageListeners::schedule(bot, auth));
    bot.getEvents().onCommand("save_schedule", MessageListeners::saveSchedule(bot, auth));

    bot.getEvents().onAnyMessage(MessageListeners::anyMessage(bot));
}

void ScheduleSaverBot::start()
{
    try
    {
        cout << "Bot username: " << bot.getApi().getMe()->username << "\n";
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true)
        {
            cout << "Long poll started\n";
            longPoll.start();
        }
    }
    catch (exception &e)
    {
        cout << "error: " << e.what() << "\n";
    }
}