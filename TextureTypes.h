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

class SmallPipe : public Terrain
{
public:
    SmallPipe() : Terrain(Position(), "smallpipe", 180) {}
};

class SmallPipeHelper : public Terrain
{
public:
    SmallPipeHelper() : Terrain(Position(), "smallpipehelper", 180) {}
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

class Castle : public Terrain
{
public:
    Castle() : Terrain(Position(), "castle", 343) {}
};

class CastleHelper : public Terrain
{
public:
    CastleHelper() : Terrain(Position(), "castlehelper",50) {}
};

class Cliff : public Terrain
{
public:
    Cliff() : Terrain(Position(), "cliff", -500) {}
};

class HillBegin : public Terrain
{
public:
    HillBegin() :  Terrain(Position(), "hillbegin", 100) {}
};

class Hill : public Terrain
{
public:
    Hill() :  Terrain(Position(), "hill", 100) {}
};

class HillEnd : public Terrain
{
public:
    HillEnd() :  Terrain(Position(), "hillend", 100) {}
};

class MediumHillBegin : public Terrain
{
public:
    MediumHillBegin() :  Terrain(Position(), "mediumhillbegin", 150) {}
};

class MediumHill : public Terrain
{
public:
    MediumHill() :  Terrain(Position(), "mediumhill", 150) {}
};

class MediumHillEnd : public Terrain
{
public:
    MediumHillEnd() :  Terrain(Position(), "mediumhillend", 150) {}
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
