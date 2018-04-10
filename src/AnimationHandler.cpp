
#include "AnimationHandler.hpp"


AnimationModelKeyframe::AnimationModelKeyframe(float frameLength,
                                               float frLegTopRot,
                                               float frLegBotRot,
                                               float flLegTopRot,
                                               float flLegBotRot,
                                               float brLegTopRot,
                                               float brLegBotRot,
                                               float blLegTopRot,
                                               float blLegBotRot)
        : frameTime(frameLength)
        , frLegTopRot(frLegTopRot)
        , frLegBotRot(frLegBotRot)
        , flLegTopRot(flLegTopRot)
        , flLegBotRot(flLegBotRot)
        , brLegTopRot(brLegTopRot)
        , brLegBotRot(brLegBotRot)
        , blLegTopRot(blLegTopRot)
        , blLegBotRot(blLegBotRot)
{}

AnimationModelKeyframe::AnimationModelKeyframe()
{
    Horse horse;
    this->frameTime = 1.0f;
    this->frLegTopRot = horse.frLegTop->getRotation().z;
    this->frLegBotRot = horse.frLegBot->getRotation().z;
    this->flLegTopRot = horse.flLegTop->getRotation().z;
    this->flLegBotRot = horse.flLegBot->getRotation().z;
    this->brLegTopRot = horse.brLegTop->getRotation().z;
    this->brLegBotRot = horse.brLegBot->getRotation().z;
    this->blLegTopRot = horse.blLegTop->getRotation().z;
    this->blLegBotRot = horse.blLegBot->getRotation().z;
}



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
        state.currentAnim = type;
        state.timeCounter = 0.0f;
    }
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

        AnimationState* state = &_horseAnimStates[i];
        std::shared_ptr<Horse> horse = _horses[i];
        if (!state->isAnimating)
        {
            tickIdleAnim(horse);
            return;
        }

        switch(state->currentAnim)
        {
            case AnimationType::IDLE:
                tickIdleAnim(horse);
                break;
            case AnimationType::WALK:
                tickWalkAnim(deltaTime, horse, *state);
                break;
            case AnimationType::RUN:
                tickRunAnim(deltaTime, horse, *state);
                break;
            case AnimationType::TURN:
                tickTurnAnim(deltaTime, horse, *state);
                break;
        }
    }
}

void AnimationHandler::tickIdleAnim(std::shared_ptr<Horse> horse)
{
    applyModelKeyFrame(HorseIdleModelAnim[0], horse);
}

void AnimationHandler::tickWalkAnim(float deltaTime, std::shared_ptr<Horse> horse, AnimationState& state)
{

    float currentAnimTime = state.timeCounter + deltaTime;
    float walkAnimDuration = HorseWalkModelAnim.back().frameTime;

    if (currentAnimTime >= walkAnimDuration)
    {
        applyModelKeyFrame(HorseWalkModelAnim.back(), horse);
        state.timeCounter = 0;
        std::cout << "TODO: FINISH STOP COND WALK ANIM" << std::endl;
    }

    AnimationModelKeyframe frame1;
    AnimationModelKeyframe frame2;

    for (unsigned int i = 0; i < HorseWalkModelAnim.size() - 1; ++i)
    {
        if (currentAnimTime > HorseWalkModelAnim[i].frameTime)
        {
            frame1 = HorseWalkModelAnim[i];
            frame2 = HorseWalkModelAnim[i + 1];
            break;
        }
    }

    float ratio = (currentAnimTime - frame1.frameTime) / (frame2.frameTime - frame1.frameTime);
    applyModelKeyFrame(ratio, frame1, frame2, horse);

    //

    /*
 *
    //if were at or past the end time for the rotate anim, set to end of anim and set anim to previous anim
    if (currentAnimTime >= RotateAnimDuration)
    {
        horse->mutateRotation().y = state.initRotation + state.rotateDir * RotateSpeed * RotateAnimDuration;
        state.timeCounter = 0.0f;
        state.currentAnim = state.previousAnim;
        state.previousAnim = AnimationType::TURN;
        state.initRotation = horse->getRotation().y;
        return;
    }
    */

}

void AnimationHandler::tickRunAnim(float deltaTime, std::shared_ptr<Horse> horse, AnimationState& state)
{

    float currentAnimTime = state.timeCounter + deltaTime;
    float runAnimDuration = HorseRunModelAnim.back().frameTime;



}

void AnimationHandler::tickTurnAnim(float deltaTime, std::shared_ptr<Horse> horse, AnimationState& state)
{

    float currentAnimTime = state.timeCounter + deltaTime;

    if (state.timeCounter == 0.0f)
    {
        //Beginning of anim
        //Randomize turn direction.
        std::cout << "TODO: RANDOMIZE TURN DIR" << std::endl;
    }

    //if were at or past the end time for the rotate anim, set to end of anim and set anim to previous anim
    if (currentAnimTime >= RotateAnimDuration)
    {
        horse->mutateRotation().y = state.initRotation + state.rotateDir * RotateSpeed * RotateAnimDuration;
        state.timeCounter = 0.0f;
        state.currentAnim = state.previousAnim;
        state.previousAnim = AnimationType::TURN;
        state.initRotation = horse->getRotation().y;
        return;
    }

    //Step anim
    float totalDegrees = RotateSpeed * RotateAnimDuration;
    float rotation = totalDegrees * (currentAnimTime / RotateAnimDuration);

    horse->mutateRotation().y = state.initRotation + rotation;
}

void AnimationHandler::applyModelKeyFrame(AnimationModelKeyframe keyframe, std::shared_ptr<Horse> horse)
{
    horse->frLegTop->mutateRotation().z = keyframe.frLegTopRot;
    horse->frLegBot->mutateRotation().z = keyframe.frLegBotRot;
    horse->flLegTop->mutateRotation().z = keyframe.flLegTopRot;
    horse->flLegBot->mutateRotation().z = keyframe.flLegBotRot;
    horse->brLegTop->mutateRotation().z = keyframe.brLegTopRot;
    horse->brLegBot->mutateRotation().z = keyframe.brLegBotRot;
    horse->blLegTop->mutateRotation().z = keyframe.blLegTopRot;
    horse->blLegBot->mutateRotation().z = keyframe.blLegBotRot;
}

void AnimationHandler::applyModelKeyFrame(float ratio, AnimationModelKeyframe keyframe1, AnimationModelKeyframe keyframe2, std::shared_ptr<Horse> horse)
{
    horse->frLegTop->mutateRotation().z = ratio * keyframe1.frLegTopRot + (1 - ratio) * keyframe2.frLegTopRot;
    horse->frLegBot->mutateRotation().z = ratio * keyframe1.frLegBotRot + (1 - ratio) * keyframe2.frLegBotRot;
    horse->flLegTop->mutateRotation().z = ratio * keyframe1.flLegTopRot + (1 - ratio) * keyframe2.flLegTopRot;
    horse->flLegBot->mutateRotation().z = ratio * keyframe1.flLegBotRot + (1 - ratio) * keyframe2.flLegBotRot;
    horse->brLegTop->mutateRotation().z = ratio * keyframe1.brLegTopRot + (1 - ratio) * keyframe2.brLegTopRot;
    horse->brLegBot->mutateRotation().z = ratio * keyframe1.brLegBotRot + (1 - ratio) * keyframe2.brLegBotRot;
    horse->blLegTop->mutateRotation().z = ratio * keyframe1.blLegTopRot + (1 - ratio) * keyframe2.blLegTopRot;
    horse->blLegBot->mutateRotation().z = ratio * keyframe1.blLegBotRot + (1 - ratio) * keyframe2.blLegBotRot;
}




void AnimationHandler::tickMovementAnim(float deltaTime)
{

}





void AnimationHandler::tickCollisionDetect()
{

    for (unsigned int i = 0; i < _horses.size(); ++i)
    {
        for (unsigned int j = 0; i < _horses.size(); ++j)
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


