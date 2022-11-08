#include <toml++/toml.h>
#include "Config.hpp"
#include <string_view>

std::vector<std::string> Config::varsToSetup()
{
    using namespace std::literals;
    std::vector<std::string> vars;
    auto config = toml::parse_file("config.toml");
    std::string_view bot_secret = config["telegram"]["bot_secret"].value_or(""sv);
    std::string_view app_secret = config["google"]["app_secret"].value_or(""sv);
    if(bot_secret.empty()) {
        vars.push_back("telegram.bot_secret");
    }
    if(app_secret.empty()) {
        vars.push_back("google.app_secret");
    }
    return vars;
}

void Config::setupVars(const std::vector<std::string> &vars)
{
}
