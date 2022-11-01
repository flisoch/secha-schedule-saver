#include "ScheduleSaverBot.hpp"

ScheduleSaverBot::ScheduleSaverBot()
    : token{getenv("SECHA_BOT_TOKEN")},
      bot{token}
{
    setEventListeners();
}

void ScheduleSaverBot::setEventListeners()
{
    bot.getEvents().onCommand("start", MessageListeners::start(bot));
    bot.getEvents().onCommand("auth", MessageListeners::auth(bot));
    bot.getEvents().onCommand("schedule", MessageListeners::schedule(bot));
    bot.getEvents().onCommand("save_schedule", MessageListeners::saveSchedule(bot));

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