
#pragma once

#include "AxisLines.hpp"
#include "Cube.hpp"
#include "IRenderAxisNode.hpp"
#include "../PNGLoader.hpp"


class HorseTorso;
class HorseTail;
class HorseLegTop;
class HorseLegBot;
class HorseLegHoof;
class HorseNeck;
class HorseHead;



class Horse : public IRenderNode
{

public:
    Horse();

    void showAxis(bool active);

    void doAnim(bool value);

    void tickAnim();

    std::shared_ptr<HorseTorso>   frontTorso;
    std::shared_ptr<HorseTorso>   backTorso;
    std::shared_ptr<HorseTail>    tail;
    std::shared_ptr<HorseNeck>    neck;
    std::shared_ptr<HorseHead>    head;
    std::shared_ptr<HorseLegTop>  frLegTop;
    std::shared_ptr<HorseLegBot>  frLegBot;
    std::shared_ptr<HorseLegHoof> frLegHoof;
    std::shared_ptr<HorseLegTop>  flLegTop;
    std::shared_ptr<HorseLegBot>  flLegBot;
    std::shared_ptr<HorseLegHoof> flLegHoof;
    std::shared_ptr<HorseLegTop>  brLegTop;
    std::shared_ptr<HorseLegBot>  brLegBot;
    std::shared_ptr<HorseLegHoof> brLegHoof;
    std::shared_ptr<HorseLegTop>  blLegTop;
    std::shared_ptr<HorseLegBot>  blLegBot;
    std::shared_ptr<HorseLegHoof> blLegHoof;

private:

    unsigned int _animLength = 4;
    bool _doAnim = false;

    glm::vec3 initfrTopRot;
    glm::vec3 initflTopRot;
    glm::vec3 initbrTopRot;
    glm::vec3 initblTopRot;
    glm::vec3 initfrBotRot;
    glm::vec3 initflBotRot;
    glm::vec3 initbrBotRot;
    glm::vec3 initblBotRot;

    unsigned int frFrameStart = 3;
    unsigned int flFrameStart = 1;
    unsigned int brFrameStart = 2;
    unsigned int blFrameStart = 0;

    unsigned int frFrameState;
    unsigned int flFrameState;
    unsigned int brFrameState;
    unsigned int blFrameState;

    void backLegFrame(unsigned int frameVal, std::shared_ptr<HorseLegTop> top, std::shared_ptr<HorseLegBot> bot);
    void frontLegFrame(unsigned int frameVal, std::shared_ptr<HorseLegTop> top, std::shared_ptr<HorseLegBot> bot);

};


class HorseTorso : public IRenderAxisNode
{
public:
    HorseTorso(glm::vec3 color, std::string name);
};

class HorseTail : public IRenderAxisNode
{
public:
    explicit HorseTail(std::string name);
};

class HorseLegTop : public IRenderAxisNode
{
public:
    explicit HorseLegTop(std::string name);
};

class HorseLegBot : public IRenderAxisNode
{
public:
    explicit HorseLegBot(std::string name);
};

class HorseLegHoof : public IRenderAxisNode
{
public:
    explicit HorseLegHoof(std::string name);
};

class HorseNeck : public IRenderAxisNode
{
public:
    HorseNeck();
};

class HorseHead : public IRenderAxisNode
{
public:
    HorseHead();
};
