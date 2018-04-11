
#include "AnimationHandler.hpp"

AnimationModelKeyframe::AnimationModelKeyframe(float frameLength,
                                               float frLegTopRot,
                                               float frLegBotRot,
                                               float flLegTopRot,
                                               float flLegBotRot,
                                               float brLegTopRot,
                                               float brLegBotRot,
                                               float blLegTopRot,
                                               float blLegBotRot,
                                               float neckRot,
                                               float tailRot)
        : frameTime(frameLength)
        , frLegTopRot(frLegTopRot)
        , frLegBotRot(frLegBotRot)
        , flLegTopRot(flLegTopRot)
        , flLegBotRot(flLegBotRot)
        , brLegTopRot(brLegTopRot)
        , brLegBotRot(brLegBotRot)
        , blLegTopRot(blLegTopRot)
        , blLegBotRot(blLegBotRot)
        , neckRot(neckRot)
        , tailRot(tailRot)
{}

AnimationHandler::AnimationHandler(std::vector<std::shared_ptr<Horse>> horses)
{
    _horses = horses;

    for (std::shared_ptr<Horse> horse : _horses)
    {
        AnimationState state{};
        state.initRotation = horse->getRotation().y;
        _horseAnimStates.push_back(state);
    }
}


void AnimationHandler::enableAnimations(bool value)
{
    for (AnimationState& state : _horseAnimStates)
    {
        state.isAnimating = value;
    }
}

void AnimationHandler::setAnimationType(AnimationType type)
{
    for (AnimationState& state : _horseAnimStates)
    {
        setAnimationType(type, state);
    }
}

void AnimationHandler::setAnimationType(AnimationType type, AnimationState &state)
{
    state.previousAnim = state.currentAnim;
    state.currentAnim = type;
    state.timeCounter = 0.0f;
}


void AnimationHandler::tick(float deltaTime)
{
    tickModelAnim(deltaTime);
    tickMovementAnim(deltaTime);
    tickCollisionDetect();
}



void AnimationHandler::tickModelAnim(float deltaTime)
{

    for (unsigned int i = 0; i < _horseAnimStates.size(); ++i)
    {

        std::shared_ptr<Horse> horse = _horses[i];
        if (!_horseAnimStates[i].isAnimating)
        {
            tickIdleAnim(horse);
            return;
        }

        switch(_horseAnimStates[i].currentAnim)
        {
            case AnimationType::IDLE:
                tickIdleAnim(horse);
                break;
            case AnimationType::WALK:
                tickWalkAnim(deltaTime, horse, i);
                break;
            case AnimationType::RUN:
                tickRunAnim(deltaTime, horse, i);
                break;
            case AnimationType::TURN:
                tickTurnAnim(deltaTime, horse, i);
                break;
        }
    }
}

void AnimationHandler::tickIdleAnim(std::shared_ptr<Horse> horse)
{
    applyModelKeyFrame(HorseIdleModelAnim[0], horse);
}

void AnimationHandler::tickWalkAnim(float deltaTime, std::shared_ptr<Horse> horse, unsigned int& animStateIndex)
{

    float currentAnimTime = _horseAnimStates[animStateIndex].timeCounter + deltaTime;
    float walkAnimDuration = HorseWalkModelAnim.back().frameTime;

    if (currentAnimTime >= walkAnimDuration)
    {
        applyModelKeyFrame(HorseWalkModelAnim.back(), horse);
        _horseAnimStates[animStateIndex].timeCounter = 0;
        return;
    }

    AnimationModelKeyframe frame1;
    AnimationModelKeyframe frame2;

    for (unsigned int i = 1; i < HorseWalkModelAnim.size(); ++i)
    {
        float timeim1 = HorseWalkModelAnim[i - i].frameTime;
        float timei = HorseWalkModelAnim[i].frameTime;
        if (currentAnimTime < timei && currentAnimTime > timeim1)
        {
            frame1 = HorseWalkModelAnim[i - 1];
            frame2 = HorseWalkModelAnim[i];
            break;
        }
    }

    float ratio = (currentAnimTime - frame1.frameTime) / (frame2.frameTime - frame1.frameTime);
    applyModelKeyFrame(ratio, frame1, frame2, horse);

    _horseAnimStates.at(animStateIndex).timeCounter += deltaTime;
}

void AnimationHandler::tickRunAnim(float deltaTime, std::shared_ptr<Horse> horse, unsigned int& animStateIndex)
{

    float currentAnimTime = _horseAnimStates[animStateIndex].timeCounter + deltaTime;
    float walkAnimDuration = HorseRunModelAnim.back().frameTime;

    if (currentAnimTime >= walkAnimDuration)
    {
        applyModelKeyFrame(HorseRunModelAnim.back(), horse);
        _horseAnimStates[animStateIndex].timeCounter = 0;
        return;
    }

    AnimationModelKeyframe frame1;
    AnimationModelKeyframe frame2;

    for (unsigned int i = 1; i < HorseRunModelAnim.size(); ++i)
    {
        float timeim1 = HorseRunModelAnim[i - i].frameTime;
        float timei = HorseRunModelAnim[i].frameTime;
        if (currentAnimTime < timei && currentAnimTime > timeim1)
        {
            frame1 = HorseRunModelAnim[i - 1];
            frame2 = HorseRunModelAnim[i];
            break;
        }
    }

    float ratio = (currentAnimTime - frame1.frameTime) / (frame2.frameTime - frame1.frameTime);
    applyModelKeyFrame(ratio, frame1, frame2, horse);

    _horseAnimStates.at(animStateIndex).timeCounter += deltaTime;

}

void AnimationHandler::tickTurnAnim(float deltaTime, std::shared_ptr<Horse> horse, unsigned int& animStateIndex)
{

    float currentAnimTime = _horseAnimStates[animStateIndex].timeCounter + deltaTime;

    if (_horseAnimStates[animStateIndex].timeCounter == 0.0f)
    {
        //Randomize turn direction.
        _horseAnimStates[animStateIndex].rotateDir = (_bernoulli(_randomGen)) == 1 ? 1 : -1;
        std::cout << "rotate dir: " << _horseAnimStates[animStateIndex].rotateDir << std::endl;
    }

    //if were at or past the end time for the rotate anim, set to end of anim and set anim to previous anim
    if (currentAnimTime >= RotateAnimDuration)
    {
        horse->setRotY(_horseAnimStates[animStateIndex].initRotation + _horseAnimStates[animStateIndex].rotateDir * RotateSpeed * RotateAnimDuration);
        _horseAnimStates[animStateIndex].timeCounter = 0.0f;
        _horseAnimStates[animStateIndex].currentAnim = _horseAnimStates[animStateIndex].previousAnim;
        _horseAnimStates[animStateIndex].previousAnim = AnimationType::TURN;
        _horseAnimStates[animStateIndex].initRotation = horse->getRotation().y;
        return;
    }

    //Step anim
    float totalDegrees = RotateSpeed * RotateAnimDuration;
    float rotation = _horseAnimStates[animStateIndex].rotateDir * totalDegrees * (currentAnimTime / RotateAnimDuration);

    _horseAnimStates[animStateIndex].timeCounter = currentAnimTime;

    horse->setRotY(_horseAnimStates[animStateIndex].initRotation + rotation);
}

void AnimationHandler::applyModelKeyFrame(AnimationModelKeyframe keyframe, std::shared_ptr<Horse> horse)
{
    horse->frLegTop->setRotZ(keyframe.frLegTopRot);
    horse->frLegBot->setRotZ(keyframe.frLegBotRot);
    horse->flLegTop->setRotZ(keyframe.flLegTopRot);
    horse->flLegBot->setRotZ(keyframe.flLegBotRot);
    horse->brLegTop->setRotZ(keyframe.brLegTopRot);
    horse->brLegBot->setRotZ(keyframe.brLegBotRot);
    horse->blLegTop->setRotZ(keyframe.blLegTopRot);
    horse->blLegBot->setRotZ(keyframe.blLegBotRot);
    horse->neck->setRotZ(keyframe.neckRot);
    horse->tail->setRotZ(keyframe.tailRot);
}

void AnimationHandler::applyModelKeyFrame(float ratio, AnimationModelKeyframe keyframe1, AnimationModelKeyframe keyframe2, std::shared_ptr<Horse> horse)
{
    horse->frLegTop->setRotZ(keyframe1.frLegTopRot + ratio * (keyframe2.frLegTopRot - keyframe1.frLegTopRot));
    horse->frLegBot->setRotZ(keyframe1.frLegBotRot + ratio * (keyframe2.frLegBotRot - keyframe1.frLegBotRot));
    horse->flLegTop->setRotZ(keyframe1.flLegTopRot + ratio * (keyframe2.flLegTopRot - keyframe1.flLegTopRot));
    horse->flLegBot->setRotZ(keyframe1.flLegBotRot + ratio * (keyframe2.flLegBotRot - keyframe1.flLegBotRot));
    horse->brLegTop->setRotZ(keyframe1.brLegTopRot + ratio * (keyframe2.brLegTopRot - keyframe1.brLegTopRot));
    horse->brLegBot->setRotZ(keyframe1.brLegBotRot + ratio * (keyframe2.brLegBotRot - keyframe1.brLegBotRot));
    horse->blLegTop->setRotZ(keyframe1.blLegTopRot + ratio * (keyframe2.blLegTopRot - keyframe1.blLegTopRot));
    horse->blLegBot->setRotZ(keyframe1.blLegBotRot + ratio * (keyframe2.blLegBotRot - keyframe1.blLegBotRot));
    horse->neck->setRotZ(keyframe1.neckRot + ratio * (keyframe2.neckRot - keyframe1.neckRot));
    horse->tail->setRotZ(keyframe1.tailRot + ratio * (keyframe2.tailRot - keyframe1.tailRot));
}




void AnimationHandler::tickMovementAnim(float deltaTime)
{



}





void AnimationHandler::tickCollisionDetect()
{

    for (unsigned int i = 0; i < _horses.size(); ++i)
    {
        for (unsigned int j = 0; j < _horses.size(); ++j)
        {

            if (i == j) {continue;}

            if (getDistance(_horses[i], _horses[j]) < HorseRadius)
            {
                std::cout << "Collision detected between horses " << i << " and " << j << std::endl;
            }

        }
    }

}

float AnimationHandler::getDistance(std::shared_ptr<Horse> horse1, std::shared_ptr<Horse> horse2)
{
    glm::vec3 pos1 = horse1->getPosition();
    glm::vec3 pos2 = horse2->getPosition();

    return (float)glm::sqrt(
              glm::pow(pos2.x - pos1.x, 2)
            + glm::pow(pos2.y - pos1.y, 2)
            + glm::pow(pos2.z - pos1.z, 2));
}

