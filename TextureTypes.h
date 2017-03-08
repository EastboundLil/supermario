#ifndef TEXTURETYPES_H
#define TEXTURETYPES_H

#include "Terrain.h"

class Ground : public Terrain
{
public:
    Ground() : Terrain(Position(), "ground", 50) {}
};

class Pipe : public Terrain
{
public:
    Pipe() : Terrain(Position(), "pipe", 230) {}
};

class End : public Terrain
{
public:
    End() : Terrain(Position(), "end", 500) {}
};

#endif // TEXTURETYPES_H
