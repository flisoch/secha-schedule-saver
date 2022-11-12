#include <string>

#include "Config.hpp"
#include "gtest/gtest.h"

TEST(Config, varsToSetupReturnsSecretVars)
{
    Config &c = Config::instance();
    auto vars = c.varsToSetup();
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars[0], Config::VAR_APP_CLIENT_ID);
}

TEST(Config, isSetupReturnsFalseByDefault)
{
    Config &c = Config::instance();
    ASSERT_EQ(c.isSetUp(), false);
}
