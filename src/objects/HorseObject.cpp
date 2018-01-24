
#include "HorseObject.hpp"

HorseObject::HorseObject(Shader &shader) : IRenderObject(shader)
{

    //Torso front
    addHorsePart(glm::vec3(-0.25f, -0.1f, -0.1f), glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(.0f, 0.0f, 0.0f));
    //Torso back
    addHorsePart(glm::vec3(0.0f, -0.1f, -0.1f), glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f));

    //Tail
    addHorsePart(glm::vec3(0.23f, 0.05f, -0.025f), glm::vec3(0.35f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, -80.0f), glm::vec3(0.2f, 0.2f, 0.2f));

    //--Front right leg
    //Hoof
    addHorsePart(glm::vec3(-0.24f, -0.5f, -0.09f), glm::vec3(0.075f, 0.07f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f));
    //Leg Bottom
    addHorsePart(glm::vec3(-0.24f, -0.43f, -0.09f), glm::vec3(0.075f, 0.2f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f));
    //Hoof
    addHorsePart(glm::vec3(-0.24f, -0.23f, -0.09f), glm::vec3(0.075f, 0.2f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

    //--Front left leg
    //Hoof
    addHorsePart(glm::vec3(-0.24f, -0.5f, 0.015f), glm::vec3(0.075f, 0.07f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f));
    //Leg Bottom
    addHorsePart(glm::vec3(-0.24f, -0.43f, 0.015f), glm::vec3(0.075f, 0.2f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f));
    //Hoof
    addHorsePart(glm::vec3(-0.24f, -0.23f, 0.015f), glm::vec3(0.075f, 0.2f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

    //--Back right leg
    //Hoof
    addHorsePart(glm::vec3(0.165f, -0.5f, -0.09f), glm::vec3(0.075f, 0.07f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f));
    //Leg Bottom
    addHorsePart(glm::vec3(0.165f, -0.43f, -0.09f), glm::vec3(0.075f, 0.2f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f));
    //Hoof
    addHorsePart(glm::vec3(0.165f, -0.23f, -0.09f), glm::vec3(0.075f, 0.2f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

    //--Back left leg
    //Hoof
    addHorsePart(glm::vec3(0.165f, -0.5f, 0.015f), glm::vec3(0.075f, 0.07f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f));
    //Leg Bottom
    addHorsePart(glm::vec3(0.165f, -0.43f, 0.015f), glm::vec3(0.075f, 0.2f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f));
    //Hoof
    addHorsePart(glm::vec3(0.165f, -0.23f, 0.015f), glm::vec3(0.075f, 0.2f, 0.075f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

    //Neck
    addHorsePart(glm::vec3(-0.15f, -0.1f, -0.05f), glm::vec3(0.1f, 0.3f, 0.1f), glm::vec3(0.0f, 0.0f, 45.0f), glm::vec3(0.6f, 0.6f, 0.6f));

    //Head
    addHorsePart(glm::vec3(-0.45f, 0.0f, -0.04f), glm::vec3(0.08f, 0.18f, 0.08f), glm::vec3(0.0f, 0.0f, -25.0f), glm::vec3(0.7f, 0.7f, 0.7f));

    setPosition(glm::vec3(0.45f, 0.5f, 0.4f));

}

void HorseObject::render(glm::mat4 vpMatrix)
{

    for (const std::shared_ptr<IRenderObject> &part : _parts)
    {
        part->render(vpMatrix * _modelMatrix);
    }
}

void HorseObject::addHorsePart(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotation, glm::vec3 color)
{

    std::shared_ptr<IRenderObject> part = std::dynamic_pointer_cast<IRenderObject, CubeObject>(std::make_shared<CubeObject>(_shader, color));
    part->setPosition(translation);
    part->setScale(scale);
    part->setRotation(rotation);

    _parts.emplace_back(part);
}
