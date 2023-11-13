#pragma once
#ifndef FILESYSTEM
#define FILESYSTEM

#include <fstream>
#include <string>
#include <vector>

namespace gfs
{
    std::vector<std::vector<std::string>> readFromFile(std::string filename, int countOfData, char datatype = 'D', bool untilInterrupt = false, int startPosition = 0);
}

#endif
