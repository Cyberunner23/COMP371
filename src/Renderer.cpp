
#include "Renderer.hpp"

Renderer::Renderer(std::unique_ptr<Shader>&& genericShader,
                   std::unique_ptr<Shader>&& blendedShader,
                   std::unique_ptr<Shader>&& shadowShader,
                   std::shared_ptr<Camera> mainCamera)
        : _genericShader(std::move(genericShader))
        , _blendedShader(std::move(blendedShader))
        , _shadowShader(std::move(shadowShader))
        , _mainCamera(std::move(mainCamera))
        , _shadowCamera(std::make_shared<Camera>(SHADOW_WIDTH, SHADOW_HEIGHT, 45.0))
        , _polygonMode(GL_TRIANGLES)
        , _texRatio(0.0f)
{
    _shadowCamera->setPos(glm::vec3(0.0f, 30.0f, 0.01f));

    //Setup texture
    glGenTextures(1, &_depthMap);
    glBindTexture(GL_TEXTURE_2D, _depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Attach
    glGenFramebuffers(1, &_depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer construction failed!" << std::endl;
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


void Renderer::render()
{

    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    //Shadow pass
    _shadowCamera->forceGLViewportResize();
    for (const std::shared_ptr<IRenderNode>& root : _objects)
    {
        recursiveShadowRender(_shadowCamera->getViewProjectionMatrix(), glm::mat4(1.0f), root);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //Render all objects in world
    _mainCamera->forceGLViewportResize();
    for (const std::shared_ptr<IRenderNode>& root : _objects)
    {
        recursiveRender(_mainCamera->getViewProjectionMatrix(), glm::mat4(1.0f), root);
    }
}


void Renderer::recursiveShadowRender(glm::mat4 vpMatrix, glm::mat4 CTM, std::shared_ptr<IRenderNode> currentNode)
{
    if (currentNode == nullptr) return;

    //_shadowCamera->setPos(_light.lightPos);

    //Compute new transformation
    glm::mat4 currentModelMat = CTM * currentNode->getModelMatrix();
    std::vector<std::shared_ptr<IRenderNode>>* children = currentNode->getChildren();

    currentNode->setFinalModelMat(currentModelMat);

    //Render
    VAOGuard vGuard(currentNode->getVAO());
    glBindTexture(GL_TEXTURE_2D, _depthMap);
    ShaderGuard sGuard(_shadowShader);
    glm::mat4 MVP = vpMatrix * currentModelMat;

    if (!_shadowShader->setUniformM4fv("MVP", MVP))
    {
        std::cout << "ERROR: failed to set the MVP" << std::endl;
    }


    //glClear(GL_DEPTH_BUFFER_BIT);
    glDrawArrays(currentNode->getRenderMode(), 0, (GLsizei)currentNode->getMeshSize());



    //Recurse down the tree, render the child objects
    for (std::shared_ptr<IRenderNode> const &node : *children)
    {
        recursiveShadowRender(vpMatrix, currentModelMat, node);
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
        tGuard = std::make_unique<TextureGuard>(_blendedShader.get(), 0, "textureSampler", currentNode->getTexture());
        tGuard = std::make_unique<TextureGuard>(_blendedShader.get(), 1, "shadowMap", _depthMap);
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

        //Shadow
        glm::mat4 shadowVP = _shadowCamera->getViewProjectionMatrix() * currentModelMat;
        if (!_blendedShader->setUniformM4fv("ShadowMVP", shadowVP))
        {
            std::cout << "ERROR: failed to set the LightSpaceVP" << std::endl;
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
