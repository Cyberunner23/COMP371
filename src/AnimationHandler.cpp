
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
        : _randomGen(std::random_device()())
        , _speedDistrib(1.0f, 5.0f)
        , _distanceDistrib(10.0f, 30.0f)
{
    _horses = horses;

    for (std::shared_ptr<Horse> horse : _horses)
    {
        AnimationState state {};
        state.initRotation = horse->getRotation().y;
        _horseAnimStates.push_back(state);

        MovementState mState {};
        _horseMovementStates.push_back(mState);
    }
}


void AnimationHandler::enableAnimations(bool value)
{
    for (AnimationState& state : _horseAnimStates)
    {
        state.isAnimating = value;
    }

    for (MovementState& state : _horseMovementStates)
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
    //tickMovementAnim(deltaTime);
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

    for (unsigned int i = 0; i < _horseAnimStates.size(); ++i)
    {

        //if colliding and not the one to move, skip move anim tick
        if (_horseAnimStates[i].isColliding && !_horseAnimStates[i].isChosenToMove) {continue;}

        //If turning, dont move
        if (_horseAnimStates[i].currentAnim == AnimationType::TURN) {continue;}

        //If were done, start the turn animation
        if (_horseAnimStates[i].movementTimeCounter > _horseMovementStates[i].movementLength)
        {
            //We have reached the end of the movement phase, time to turn
            _horseAnimStates[i].movementTimeCounter = 0;
            _horseAnimStates[i].previousAnim = _horseAnimStates[i].currentAnim;
            _horseAnimStates[i].currentAnim = AnimationType::TURN;
            continue;
        }

        //If beginning of movement
        if (_horseAnimStates[i].currentAnim != AnimationType::TURN && _horseAnimStates[i].movementTimeCounter == 0.0f)
        {
            _horseAnimStates[i].movementSpeed = (float)_speedDistrib(_randomGen);
            _horseAnimStates[i].movementLength = (float)_distanceDistrib(_randomGen);
        }


        //do the movement

        float currentTime = _horseAnimStates[i].movementTimeCounter + deltaTime;
        float currentAngle = _horses[i]->getRotation().y;
        float distanceToMove = deltaTime * _horseAnimStates[i].movementSpeed;

        std::cout << "deltatime: " << deltaTime << " movementspeed: " << _horseAnimStates[i].movementSpeed << std::endl;

        float dx = distanceToMove * glm::cos(currentAngle);
        float dz = distanceToMove * glm::sin(currentAngle);

        _horses[i]->translate(glm::vec3(dx, 0.0f, dz));

        std::cout << "Translated by x: " << dx << " z: " << dz << std::endl;

        std::cout << "oldtime: " << _horseAnimStates[i].movementTimeCounter << " newtime: " << currentTime << std::endl;
        _horseAnimStates[i].movementTimeCounter = currentTime;
    }

}





void AnimationHandler::tickCollisionDetect()
{

    //clear flags if no longer colliding
    for (unsigned int i = 0; i < _horseAnimStates.size(); ++i)
    {
        if (_horseAnimStates[i].isColliding)
        {
            bool isStillColliding = false;
            for (unsigned int j = 0; j < _horseAnimStates.size(); ++j)
            {
                if (i == j) {continue;}

                if (getDistance(_horses[i], _horses[j]) < HorseRadius)
                {
                    isStillColliding = true;
                }

                if (!isStillColliding)
                {
                    _horseAnimStates[i].isChosenToMove = false;
                    _horseAnimStates[i].isColliding = false;
                }
            }
        }
    }

    //Check for collisions
    for (unsigned int i = 0; i < _horses.size(); ++i)
    {
        for (unsigned int j = 0; j < _horses.size(); ++j)
        {

            if (i == j) {continue;}

            if (getDistance(_horses[i], _horses[j]) < HorseRadius)
            {
                std::cout << "Collision detected between horses " << i << " and " << j << std::endl;
                bool selection = _bernoulli(_randomGen) == 0;

                _horseAnimStates[i].isColliding = true;
                _horseAnimStates[j].isColliding = true;

                if (selection)
                {
                    _horseAnimStates[i].isChosenToMove = true;
                }
                else
                {
                    _horseAnimStates[j].isChosenToMove = true;
                }
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

