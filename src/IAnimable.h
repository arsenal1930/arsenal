#pragma once
#ifndef IAnimableInit
#define IAnimableInit

#include "ITextureable.h"

class IAnimable : public ITextureable {
    public:
        IAnimable(std::string path = "images/cat.jpg") : ITextureable(path) {}
};
#endif