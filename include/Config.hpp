#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <toml++/toml.h>
#include <vector>

class Config
{
public:
    static const std::string VAR_APP_CLIENT_ID;
    static const std::string VAR_SERVER_DOMAIN;
    static const std::string VAR_SERVER_PORT;

    static Config &instance();
    bool isSetUp();
    std::vector<std::string> varsToSetup();
    std::string get(const std::string &var);

private:
    Config();

    toml::table config;
};

#endif /* CONFIG_H */
