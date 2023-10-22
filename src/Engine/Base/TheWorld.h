#pragma once

#ifndef TheWorldInit
#define TheWorldInit

#include "Denizen.h"
#include <vector>

class TheWorld
{
private:
    std::vector<Denizen> denizens;

public:
    int getDenizensSize() { return denizens.size(); }
    Denizen &getDenizen(int id) { return denizens.at(id); }
    void addDenizen(Denizen &denizen) { denizens.push_back(denizen); }
};

#endif
