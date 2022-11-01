#ifndef CONNECTOR_H
#define CONNECTOR_H
#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>

inline int callPythonScript()
{
    std::string cmd = "python3 connector.py";
    int ret = system(cmd.c_str());
    return WEXITSTATUS(ret);
}


#endif /* CONNECTOR_H */
