//
// Created by cyberunner23 on 2/4/18.
//

#include "Horse.hpp"

Horse::Horse() : IRenderNode("Horse")
{

    std::shared_ptr<HorseTorso> frontTorso = std::make_shared<HorseTorso>(glm::vec3(0.0f), "FrontTorso");
    std::shared_ptr<HorseTorso> backTorso = std::make_shared<HorseTorso>(glm::vec3(0.1f), "BackTorso");

    std::shared_ptr<HorseTail> tail = std::make_shared<HorseTail>("Tail");



    std::shared_ptr<HorseLegTop>  frLegTop  = std::make_shared<HorseLegTop>("frLegTop");
    std::shared_ptr<HorseLegBot>  frLegBot  = std::make_shared<HorseLegBot>("frLegBot");
    std::shared_ptr<HorseLegHoof> frLegHoof = std::make_unique<HorseLegHoof>("frLegHoof");

    std::shared_ptr<HorseLegTop>  flLegTop  = std::make_shared<HorseLegTop>("flLegTop");
    std::shared_ptr<HorseLegBot>  flLegBot  = std::make_shared<HorseLegBot>("flLegBot");
    std::shared_ptr<HorseLegHoof> flLegHoof = std::make_unique<HorseLegHoof>("flLegHoof");

    std::shared_ptr<HorseLegTop>  brLegTop  = std::make_shared<HorseLegTop>("brLegTop");
    std::shared_ptr<HorseLegBot>  brLegBot  = std::make_shared<HorseLegBot>("brLegBot");
    std::shared_ptr<HorseLegHoof> brLegHoof = std::make_unique<HorseLegHoof>("brLegHoof");

    std::shared_ptr<HorseLegTop>  blLegTop  = std::make_shared<HorseLegTop>("blLegTop");
    std::shared_ptr<HorseLegBot>  blLegBot  = std::make_shared<HorseLegBot>("blLegBot");
    std::shared_ptr<HorseLegHoof> blLegHoof = std::make_unique<HorseLegHoof>("blLegHoof");


    frontTorso->setRotation(glm::vec3(-90.0f, 0.0f, -90.0f));
    frontTorso->setPosition(glm::vec3(0.35f, 0.52f, 0.5f));


    backTorso->setPosition(glm::vec3(0.0f, 0.25f, 0.0f));
    tail->setPosition(glm::vec3(0.0f, 0.23f, 0.0f));
    tail->setRotation(glm::vec3(0.0f, 0.0f, -80.0f));

    //Front left leg
    flLegTop->setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
    flLegTop->setPosition(glm::vec3(0.05f, 0.0375, 0.0525f));
    flLegBot->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    flLegHoof->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));

    flLegTop->addChildNode(flLegBot);
    flLegBot->addChildNode(flLegHoof);


    //Front right leg
    frLegTop->setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
    frLegTop->setPosition(glm::vec3(0.05f, 0.0375, -0.0525f));
    frLegBot->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    frLegHoof->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));

    frLegTop->addChildNode(frLegBot);
    frLegBot->addChildNode(frLegHoof);


    //Back left leg
    brLegTop->setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
    brLegTop->setPosition(glm::vec3(0.05f, 0.2025f, 0.0525f));
    brLegBot->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    brLegHoof->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));

    brLegTop->addChildNode(frLegBot);
    brLegBot->addChildNode(frLegHoof);


    //Back right leg
    blLegTop->setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
    blLegTop->setPosition(glm::vec3(0.05f, 0.2025f, -0.0525f));
    blLegBot->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    blLegHoof->setPosition(glm::vec3(0.0f, 0.2f, 0.0f));

    blLegTop->addChildNode(frLegBot);
    blLegBot->addChildNode(frLegHoof);




    frontTorso->addChildNode(backTorso);
    //frontTorso->addChildNode(flLegTop);
    frontTorso->addChildNode(frLegTop);
    frontTorso->addChildNode(flLegTop);
    backTorso->addChildNode(brLegTop);
    backTorso->addChildNode(blLegTop);
    //frLegTop->addChildNode(frLegBot);

    backTorso->addChildNode(tail);
    //backTorso->addChildNode(frLegBot);

    addChildNode(frontTorso);
}


HorseTorso::HorseTorso(glm::vec3 color, std::string name) : IRenderNode(std::move(name))
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(color);
    basePart->setScale(glm::vec3(0.2f, 0.25f, 0.2f));
    _childNodes.push_back(basePart);
}


HorseTail::HorseTail(std::string name) : IRenderNode(std::move(name))
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.2f));
    basePart->setScale(glm::vec3(0.05f, 0.35f, 0.05f));
    _childNodes.push_back(basePart);
}


HorseLegTop::HorseLegTop(std::string name) : IRenderNode(std::move(name))
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.3f));
    basePart->setScale(glm::vec3(0.075f, 0.2f, 0.075f));
    _childNodes.push_back(basePart);
}


HorseLegBot::HorseLegBot(std::string name) : IRenderNode(std::move(name))
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.4f));
    basePart->setScale(glm::vec3(0.075f, 0.2f, 0.075f));
    _childNodes.push_back(basePart);
}


HorseLegHoof::HorseLegHoof(std::string name) : IRenderNode(std::move(name))
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.5f));
    basePart->setScale(glm::vec3(0.075f, 0.07f, 0.075f));
    _childNodes.push_back(basePart);
}


HorseNeck::HorseNeck()
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.6f));
}


HorseHead::HorseHead()
{
    std::shared_ptr<Cube> basePart = std::make_shared<Cube>(glm::vec3(0.7f));
}
