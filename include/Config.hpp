#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>

class Config
{
public:
    static std::vector<std::string> varsToSetup();
    static void setupVars(const std::vector<std::string>& vars);
};

#endif /* CONFIG_H */
