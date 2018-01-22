
#pragma once

#include "IRenderObject.hpp"

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

const glm::vec3 evenColor(0.3164f, 0.3242f, 0.3359f);
const glm::vec3 oddColor(0.7031f, 0.7109f, 0.7266f);

//const glm::vec3 evenColor(1.0f, 0.0f, 0.0f);
//const glm::vec3 oddColor(1.0f, 0.2f, 1.0f);

const std::vector<glm::vec3> squareXZ = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),

        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 1.0f),
};

class FloorGridObject : public IRenderObject
{

public:

    FloorGridObject() = delete;
    explicit FloorGridObject(Shader &shader);

    virtual void render(glm::mat4 pvMatrix);


private:

    std::vector<glm::vec3> _colors;

    void uploadToGPU();

    void generateSquare(int posX, int posY);

};
