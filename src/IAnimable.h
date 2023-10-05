#pragma once
#ifndef IAnimableInit
#define IAnimableInit

#include "ITextureable.h"
class IAnimable : public ITextureable
{
    IAnimable(std::string path = "cat.png") : ITexturable(path);
};
#endif