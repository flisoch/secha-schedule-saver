#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>
#include <toml++/toml.h>

class Config
{
public:
    static const std::string VAR_BOT_SECRET;
    static const std::string VAR_APP_SECRET;
    static const std::string VAR_APP_CLIENT_ID;
    static Config& instance();
    bool isSetUp();
    std::vector<std::string> varsToSetup();
    std::string get(const std::string &var);

private:
    Config();

    toml::table config;
};

#endif /* CONFIG_H */
