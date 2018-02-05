
#pragma once

#include "Cube.hpp"
#include "IRenderNode.hpp"

class Horse : public IRenderNode
{
public:
    Horse();
};


class HorseTorso : public IRenderNode
{
public:
    HorseTorso(glm::vec3 color, std::string name);
};

class HorseTail : public IRenderNode
{
public:
    explicit HorseTail(std::string name);
};

class HorseLegTop : public IRenderNode
{
public:
    explicit HorseLegTop(std::string name);
};

class HorseLegBot : public IRenderNode
{
public:
    explicit HorseLegBot(std::string name);
};

class HorseLegHoof : public IRenderNode
{
public:
    explicit HorseLegHoof(std::string name);
};

class HorseNeck : public IRenderNode
{
public:
    HorseNeck();
};

class HorseHead : public IRenderNode
{
public:
    HorseHead();
};
