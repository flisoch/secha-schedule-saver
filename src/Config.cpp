#include "Config.hpp"
#include <iostream>
#include <string_view>
#include <toml++/toml.h>

const std::string Config::VAR_APP_CLIENT_ID = "google.app_id";
const std::string Config::VAR_APP_SECRET = "google.app_secret";
const std::string Config::VAR_BOT_SECRET = "telegram.bot_secret";
const std::string Config::VAR_SERVER_DOMAIN = "server.domain";
const std::string Config::VAR_SERVER_PORT = "server.port";


std::vector<std::string> Config::varsToSetup() {
  using namespace std::literals;
  std::vector<std::string> vars;
  config = toml::parse_file("config.toml");
  // std::string_view bot_secret =
  // config.at_path(VAR_BOT_SECRET).value_or(""sv); std::string_view app_secret
  // = config.at_path(VAR_APP_SECRET).value_or(""sv); if (bot_secret.empty())
  // {
  //     vars.push_back(Config::VAR_BOT_SECRET);
  // }
  // if (app_secret.empty())
  // {
  //     vars.push_back(Config::VAR_APP_SECRET);
  // }
  return vars;
}

bool Config::isSetUp() {
  std::vector<std::string> vars = Config::varsToSetup();
  if (!vars.empty()) {
    std::cout << "Error. Need to Set Up following variables in config.toml: \n";
    for (auto &var : vars) {
      std::cout << var << "\n";
    }
    return false;
  }

  return true;
}

std::string Config::get(const std::string &path) {
  return config.at_path(path).value_or("");
}

Config::Config() { config = toml::parse_file("config.toml"); }

Config &Config::instance() {
  static Config instance;
  return instance;
}
