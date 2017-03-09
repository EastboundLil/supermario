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

class PipeHelper : public Terrain
{
public:
    PipeHelper() : Terrain(Position(), "pipehelper", 230) {}
};

class End : public Terrain
{
public:
    End() : Terrain(Position(), "end", 500) {}
};

class EndHelper : public Terrain
{
public:
    EndHelper() : Terrain(Position(), "endhelper", 500) {}
};

class Cliff : public Terrain
{
public:
    Cliff() : Terrain(Position(), "cliff", -100) {}
};

class Stair : public Terrain
{
public:
    Stair() : Terrain(Position(), "stair", 100) {}
};



#endif // TEXTURETYPES_H
