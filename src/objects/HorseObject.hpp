
#pragma once

#include <memory>

#include "IRenderObject.hpp"
#include "CubeObject.hpp"
#include "glm/gtc/matrix_transform.hpp"

class HorseObject : public IRenderObject
{

public:

    HorseObject() = delete;
    explicit HorseObject(Shader &shader);

    virtual void render(glm::mat4 vpMatrix);

private:

    std::vector<std::shared_ptr<IRenderObject>> _parts;

    void addHorsePart(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotation, glm::vec3 color);

};
