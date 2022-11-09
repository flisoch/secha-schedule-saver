#include <string>

#include "gtest/gtest.h"
#include "Config.hpp"


TEST(Config, varsToSetupReturnsSecretVars) {
    Config& c = Config::instance();
    auto vars = c.varsToSetup();
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars[1], Config::VAR_APP_SECRET);
    ASSERT_EQ(vars[0], Config::VAR_BOT_SECRET);
}

TEST(Config, isSetupReturnsFalseByDefault) {
    Config& c = Config::instance();
    ASSERT_EQ(c.isSetUp(), false);
}
