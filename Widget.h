#ifndef WIDGET_H
#define WIDGET_H

#include "graphics.hpp"
#include "Color.h"
#include "Logger.h"

using namespace genv;

class Widget
{
public:

    Widget(std::string type) : type(type) {}

    std::string getType() { return type; }

private:
    std::string type;
};

#endif // WIDGET_H
