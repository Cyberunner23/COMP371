
#include "Renderer.hpp"

Renderer::Renderer(std::unique_ptr<Shader>&& genericShader, std::unique_ptr<Shader>&& blendedShader)
        : _polygonMode(GL_TRIANGLES)
        , _genericShader(std::move(genericShader))
        , _blendedShader(std::move(blendedShader))
        , _texRatio(0.0f)
{
    glGenFramebuffers(1, &_frameBuffer);
    glGenRenderbuffers(1, &_depthBuffer);
    glGenTextures(1, &_renderTexture);

    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

    //Setup texture
    glBindTexture(GL_TEXTURE_2D, _renderTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 2000, 2000, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Setup depth buffer
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 2000, 2000);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    //Config framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _renderTexture, 0);

    GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, buffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "WARN: Failed to create framebuffer" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Renderer::setPolygonMode(GLenum polygonMode)
{
    _polygonMode = polygonMode;
}

void Renderer::setTexRatio(float ratio)
{
    _texRatio = ratio;
}

Light& Renderer::mutateLight()
{
    return _light;
}

void Renderer::addRenderObject(std::shared_ptr<IRenderNode> rootNode)
{
    _objects.push_back(rootNode);
}


void Renderer::render(glm::mat4 vpMatrix)
{
    //Render all objects in world
    for (const std::shared_ptr<IRenderNode>& root : _objects)
    {
        recursiveRender(vpMatrix, glm::mat4(1.0f), root);
    }
}

void Renderer::recursiveRender(glm::mat4 vpMatrix, glm::mat4 CTM, std::shared_ptr<IRenderNode> currentNode)
{

    if (currentNode == nullptr) return;

    //Compute new transformation
    glm::mat4 currentModelMat = CTM * currentNode->getModelMatrix();
    std::vector<std::shared_ptr<IRenderNode>>* children = currentNode->getChildren();

    currentNode->setFinalModelMat(currentModelMat);

    //render
    VAOGuard vGuard(currentNode->getVAO());
    std::unique_ptr<ShaderGuard> sGuard;
    std::unique_ptr<TextureGuard> tGuard;

    if (!currentNode->hasTexture())
    {
        sGuard = std::make_unique<ShaderGuard>(_genericShader);

        glm::mat4 MVP = vpMatrix * currentModelMat;
        if (!_genericShader->setUniformM4fv("MVP", MVP))
        {
            std::cout << "ERROR: failed to set the MVP" << std::endl;
        }
    }
    else
    {
        sGuard = std::make_unique<ShaderGuard>(_blendedShader);
        tGuard = std::make_unique<TextureGuard>(currentNode->getTexture());
        if (!_blendedShader->setUniform1f("colorTexRatio", _texRatio))
        {
            std::cout << "ERROR: failed to set the colorTexRatio" << std::endl;
        }

        glm::mat4 MM = currentModelMat;
        if (!_blendedShader->setUniformM4fv("MM", MM))
        {
            std::cout << "ERROR: failed to set the MM" << std::endl;
        }

        setLightStruct(*_blendedShader);

        glm::mat4 MVP = vpMatrix * currentModelMat;
        if (!_blendedShader->setUniformM4fv("MVP", MVP))
        {
            std::cout << "ERROR: failed to set the MVP" << std::endl;
        }
    }




    glPolygonMode(GL_FRONT_AND_BACK, _polygonMode);
    glDrawArrays(currentNode->getRenderMode(), 0, (GLsizei)currentNode->getMeshSize());


    //Recurse down the tree, render the child objects
    for (std::shared_ptr<IRenderNode> const &node : *children)
    {
        recursiveRender(vpMatrix, currentModelMat, node);
    }
}


void Renderer::setLightStruct(Shader& shader)
{
    if (!shader.setUniform3f("camPos", _light.camPos))
    {
        std::cout << "ERROR: failed to set light.camPos " << _light.camPos.x << " " << _light.camPos.y << " " << _light.camPos.z <<std::endl;
    }

    if (!shader.setUniform3f("lightPos", _light.lightPos))
    {
        std::cout << "ERROR: failed to set light.lightPos" << std::endl;
    }

    if (!shader.setUniform3f("lightColor", _light.lightColor))
    {
        std::cout << "ERROR: failed to set light.lightColor" << std::endl;
    }


    if (!shader.setUniform1f("ambientStrength", _light.ambientStrength))
    {
        std::cout << "ERROR: failed to set light.ambientStrength" << std::endl;
    }

    if (!shader.setUniform1f("diffuseStrength", _light.diffuseStrength))
    {
        std::cout << "ERROR: failed to set light.diffuseStrength" << std::endl;
    }

    if (!shader.setUniform1f("specularStrength", _light.specularStrength))
    {
        std::cout << "ERROR: failed to set light.specularStrength" << std::endl;
    }

    if (!shader.setUniform1f("shinyCoeff", _light.shinyCoeff))
    {
        std::cout << "ERROR: failed to set light.shinyCoeff" << std::endl;
    }
}
