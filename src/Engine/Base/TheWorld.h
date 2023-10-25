#pragma once

#ifndef TheWorldInit
#define TheWorldInit

#include "Object.h"

#include <vector>

class TheWorld
{
private:
    std::vector<Object> objects;

public:
    int getObjectsSize() { return objects.size(); }
    Object &getObject(int id) { return objects.at(id); }
    void addObject(Object &object) { objects.push_back(object); }
    std::vector<Object> &getList() { return this->objects; }
};

#endif