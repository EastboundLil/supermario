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
    Cliff() : Terrain(Position(), "cliff", -500) {}
};

class Stair : public Terrain
{
public:
    Stair() : Terrain(Position(), "stair", 100) {}
};

class Stair2 : public Terrain
{
public:
    Stair2() : Terrain(Position(), "stair2", 150) {}
};

class Stair3 : public Terrain
{
public:
    Stair3() : Terrain(Position(), "stair3", 200) {}
};

class Stair4 : public Terrain
{
public:
    Stair4() : Terrain(Position(), "stair4", 250) {}
};

class Stair5 : public Terrain
{
public:
    Stair5() : Terrain(Position(), "stair5", 300) {}
};

#endif // TEXTURETYPES_H
