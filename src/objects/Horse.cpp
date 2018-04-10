
#include "Horse.hpp"

Horse::Horse() : IRenderNode("Horse")
{

    frontTorso = std::make_shared<HorseTorso>(glm::vec3(0.0f), "FrontTorso");
    backTorso = std::make_shared<HorseTorso>(glm::vec3(0.1f), "BackTorso");

    tail = std::make_shared<HorseTail>("Tail");

    neck = std::make_shared<HorseNeck>();
    head = std::make_shared<HorseHead>();

    frLegTop  = std::make_shared<HorseLegTop>("frLegTop");
    frLegBot  = std::make_shared<HorseLegBot>("frLegBot");
    frLegHoof = std::make_unique<HorseLegHoof>("frLegHoof");

    flLegTop  = std::make_shared<HorseLegTop>("flLegTop");
    flLegBot  = std::make_shared<HorseLegBot>("flLegBot");
    flLegHoof = std::make_unique<HorseLegHoof>("flLegHoof");

    brLegTop  = std::make_shared<HorseLegTop>("brLegTop");
    brLegBot  = std::make_shared<HorseLegBot>("brLegBot");
    brLegHoof = std::make_unique<HorseLegHoof>("brLegHoof");

    blLegTop  = std::make_shared<HorseLegTop>("blLegTop");
    blLegBot  = std::make_shared<HorseLegBot>("blLegBot");
    blLegHoof = std::make_unique<HorseLegHoof>("blLegHoof");


    backTorso->setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
    frontTorso->setPosition(glm::vec3(0.0f, -0.25f, 0.0f));


    //backTorso->setPosition(glm::vec3(0.0f, 0.25f, 0.0f));
    tail->setPosition(glm::vec3(0.0f, 0.23f, 0.0f));
    tail->setRotation(glm::vec3(0.0f, 0.0f, -80.0f));

    //Front left leg
    flLegTop->setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
    flLegTop->setPosition(glm::vec3(0.05f, 0.0475, 0.0525f));
    flLegBot->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    flLegHoof->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));

    flLegTop->addChildNode(flLegBot);
    flLegBot->addChildNode(flLegHoof);


    //Front right leg
    frLegTop->setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
    frLegTop->setPosition(glm::vec3(0.05f, 0.0475, -0.0525f));
    frLegBot->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    frLegHoof->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));

    frLegTop->addChildNode(frLegBot);
    frLegBot->addChildNode(frLegHoof);


    //Back left leg
    blLegTop->setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
    blLegTop->setPosition(glm::vec3(0.05f, 0.2025f, 0.0525f));
    blLegBot->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    blLegHoof->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));

    blLegTop->addChildNode(blLegBot);
    blLegBot->addChildNode(blLegHoof);


    //Back right leg
    brLegTop->setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
    brLegTop->setPosition(glm::vec3(0.05f, 0.2025f, -0.0525f));
    brLegBot->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    brLegHoof->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));

    brLegTop->addChildNode(brLegBot);
    brLegBot->addChildNode(brLegHoof);


    //Neck & head

    neck->setRotation(glm::vec3(0.0f, 0.0f, 115.0f));
    neck->setPosition(glm::vec3(0.075f, 0.06f, 0.0f));
    head->setPosition(glm::vec3(0.0f, 0.27f, 0.0f));
    head->setRotation(glm::vec3(0.0f, 0.0f, 115.0f));

    neck->addChildNode(head);


    //frontTorso->addChildNode(backTorso);


    backTorso->addChildNode(frontTorso);
    backTorso->addChildNode(brLegTop);
    backTorso->addChildNode(blLegTop);
    backTorso->addChildNode(tail);

    frontTorso->addChildNode(neck);
    frontTorso->addChildNode(frLegTop);
    frontTorso->addChildNode(flLegTop);

    addChildNode(backTorso);


    //Animation


    initfrTopRot = frLegTop->getRotation();
    initflTopRot = flLegTop->getRotation();
    initbrTopRot = brLegTop->getRotation();
    initblTopRot = blLegTop->getRotation();
    initfrBotRot = frLegBot->getRotation();
    initflBotRot = flLegBot->getRotation();
    initbrBotRot = brLegBot->getRotation();
    initblBotRot = blLegBot->getRotation();


}

Horse::Horse(glm::vec3 initPos, glm::vec3 initRot) : Horse()
{

}

void Horse::showAxis(bool active)
{
    frontTorso->showAxis(active);
    backTorso->showAxis(active);
    tail->showAxis(active);
    neck->showAxis(active);
    head->showAxis(active);
    frLegTop->showAxis(active);
    frLegBot->showAxis(active);
    frLegHoof->showAxis(active);
    flLegTop->showAxis(active);
    flLegBot->showAxis(active);
    flLegHoof->showAxis(active);
    brLegTop->showAxis(active);
    brLegBot->showAxis(active);
    brLegHoof->showAxis(active);
    blLegTop->showAxis(active);
    blLegBot->showAxis(active);
    blLegHoof->showAxis(active);
}

void Horse::tickAnim()
{
    if (_doAnim)
    {
        frFrameState = (frFrameState + 1) % _animLength; //3
        flFrameState = (flFrameState + 1) % _animLength; //1
        brFrameState = (brFrameState + 1) % _animLength; //2
        blFrameState = (blFrameState + 1) % _animLength; //0

        frontLegFrame(frFrameState, frLegTop, frLegBot);
        frontLegFrame(flFrameState, flLegTop, flLegBot);

        backLegFrame(brFrameState, brLegTop, brLegBot);
        backLegFrame(blFrameState, blLegTop, blLegBot);
    }
}

void Horse::doAnim(bool value)
{

    _doAnim = value;

    if (value)
    {
        //Start anim
        frFrameState = frFrameStart;
        flFrameState = flFrameStart;
        brFrameState = brFrameStart;
        blFrameState = blFrameStart;
    }
    else
    {
        frLegTop->setRotation(initfrTopRot);
        flLegTop->setRotation(initflTopRot);
        brLegTop->setRotation(initbrTopRot);
        blLegTop->setRotation(initblTopRot);
        frLegBot->setRotation(initfrBotRot);
        flLegBot->setRotation(initflBotRot);
        brLegBot->setRotation(initbrBotRot);
        blLegBot->setRotation(initblBotRot);
    }

}

void Horse::frontLegFrame(unsigned int frameVal, std::shared_ptr<HorseLegTop> top, std::shared_ptr<HorseLegBot> bot)
{

    glm::vec3 currTopRot = top->getRotation();
    glm::vec3 currBotRot = bot->getRotation();

    switch (frameVal)
    {
        case 0:
            currTopRot.z = -115;
            currBotRot.z = 40;
            break;
        case 1:
            currTopRot.z = -115;
            currBotRot.z = 0;
            break;
        case 2:
            currTopRot.z = -90;
            currBotRot.z = 0;
            break;
        case 3:
            currTopRot.z = -75;
            currBotRot.z = 0;
            break;
        default:
            assert(frameVal < 4);
    }

    top->setRotation(std::move(currTopRot));
    bot->setRotation(std::move(currBotRot));
}

void Horse::backLegFrame(unsigned int frameVal, std::shared_ptr<HorseLegTop> top, std::shared_ptr<HorseLegBot> bot)
{
    glm::vec3 currTopRot = top->getRotation();
    glm::vec3 currBotRot = bot->getRotation();

    switch (frameVal)
    {
        case 0:
            currTopRot.z = -75;
            currBotRot.z = 0;
            break;
        case 1:
            currTopRot.z = -90;
            currBotRot.z = 0;
            break;
        case 2:
            currTopRot.z = -95;
            currBotRot.z = -25;
            break;
        case 3:
            currTopRot.z = -90;
            currBotRot.z = 0;
            break;
        default:
            assert(frameVal < 4);
    }

    top->setRotation(std::move(currTopRot));
    bot->setRotation(std::move(currBotRot));
}


HorseTorso::HorseTorso(glm::vec3 color, std::string name) : IRenderAxisNode(std::move(name))
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(color);
    basePart->setScale(glm::vec3(0.2f, 0.25f, 0.2f));
    _childNodes.push_back(basePart);
}


HorseTail::HorseTail(std::string name) : IRenderAxisNode(std::move(name))
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.2f));
    basePart->setScale(glm::vec3(0.05f, 0.35f, 0.05f));
    _childNodes.push_back(basePart);
}


HorseLegTop::HorseLegTop(std::string name) : IRenderAxisNode(std::move(name))
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.3f));
    basePart->setScale(glm::vec3(0.075f, 0.2f, 0.075f));
    _childNodes.push_back(basePart);
}


HorseLegBot::HorseLegBot(std::string name) : IRenderAxisNode(std::move(name))
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.4f));
    basePart->setScale(glm::vec3(0.075f, 0.2f, 0.075f));
    _childNodes.push_back(basePart);
}


HorseLegHoof::HorseLegHoof(std::string name) : IRenderAxisNode(std::move(name))
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.5f));
    basePart->setScale(glm::vec3(0.075f, 0.07f, 0.075f));
    _childNodes.push_back(basePart);
}


HorseNeck::HorseNeck()
{
    _debugName = "HorseNeck";

    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.6f));
    basePart->setScale(glm::vec3(0.1f, 0.3f, 0.1f));
    _childNodes.push_back(basePart);
}


HorseHead::HorseHead()
{
    _debugName = "HorseHead";

    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.7f));
    basePart->setScale(glm::vec3(0.08f, 0.18f, 0.08f));
    _childNodes.push_back(basePart);
}
