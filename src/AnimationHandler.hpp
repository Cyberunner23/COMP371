
#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "objects/Horse.hpp"



//---------------------------------------------------------
// Types
//---------------------------------------------------------

struct AnimationModelKeyframe
{
    AnimationModelKeyframe();
    AnimationModelKeyframe(float frameLength,
                           float frLegTopRot,
                           float frLegBotRot,
                           float flLegTopRot,
                           float flLegBotRot,
                           float brLegTopRot,
                           float brLegBotRot,
                           float blLegTopRot,
                           float blLegBotRot);

    float frameTime;
    float frLegTopRot;
    float frLegBotRot;
    float flLegTopRot;
    float flLegBotRot;
    float brLegTopRot;
    float brLegBotRot;
    float blLegTopRot;
    float blLegBotRot;
};


enum class AnimationType
{
    IDLE,
    WALK,
    RUN,
    TURN
};

struct AnimationState
{
    float timeCounter = 0.0f;
    bool isAnimating = true;
    float initRotation;
    int rotateDir = 1;
    unsigned int numRepeats = 0;
    unsigned int currentRepeat = 0;
    AnimationType currentAnim  = AnimationType::IDLE;
    AnimationType previousAnim = AnimationType::IDLE;
};


class AnimationHandler
{

public:

    AnimationHandler(std::vector<std::shared_ptr<Horse>> horses);

    void enableAnimations(bool value);
    void setAnimationType(AnimationType type);

    void tick(float deltaTime);



private:


    //Degrees/second for rotation.
    const float RotateSpeed = 15;
    const float RotateAnimDuration = 1.0f;
    const float HorseRadius = 1.0f;

    std::vector<std::shared_ptr<Horse>> _horses;
    std::vector<AnimationState> _horseAnimStates;

    void tickModelAnim(float deltaTime);
    void tickIdleAnim(std::shared_ptr<Horse> horse);
    void tickWalkAnim(float deltaTime, std::shared_ptr<Horse> horse, AnimationState& state);
    void tickRunAnim(float deltaTime,  std::shared_ptr<Horse> horse, AnimationState& state);
    void tickTurnAnim(float deltaTime, std::shared_ptr<Horse> horse, AnimationState& state);

    void applyModelKeyFrame(AnimationModelKeyframe keyframe, std::shared_ptr<Horse> horse);
    //ratio: 0.0f = frame 1, 1.0f = frame 2; linear combination
    void applyModelKeyFrame(float ratio, AnimationModelKeyframe keyframe1, AnimationModelKeyframe keyframe2, std::shared_ptr<Horse> horse);

    void tickMovementAnim(float deltaTime);

    void tickCollisionDetect();
    float getDistance(std::shared_ptr<Horse> horse1, std::shared_ptr<Horse> horse2);


};


//---------------------------------------------------------
// Constants
//---------------------------------------------------------

static const std::vector<AnimationModelKeyframe> HorseIdleModelAnim
        {
                AnimationModelKeyframe()
        };

static const std::vector<AnimationModelKeyframe> HorseWalkModelAnim
        {
                //                     time  frt      frb    flt       flb   brt     brb     btl       blb
                AnimationModelKeyframe(0.0f, -75.0f,   0.0f, -115.0f,  0.0f, -95.0f, -25.0f, -75.0f,   0.0f),
                AnimationModelKeyframe(0.5f, -115.0f, 40.0f, -90.0f,   0.0f, -90.0f,   0.0f, -90.0f,   0.0f),
                AnimationModelKeyframe(1.0f, -115.0f,  0.0f, -75.0f,   0.0f, -75.0f,   0.0f, -95.0f, -25.0f),
                AnimationModelKeyframe(1.5f, -90.0f,   0.0f, -115.0f, 40.0f, -90.0f,   0.0f, -90.0f,   0.0f)
        };

static const std::vector<AnimationModelKeyframe> HorseRunModelAnim
        {
                //                     len    frt      frb    flt       flb   brt     brb     btl       blb
                AnimationModelKeyframe(0.0f,  -75.0f,   0.0f, -115.0f,  0.0f, -95.0f, -25.0f, -75.0f,   0.0f),
                AnimationModelKeyframe(0.25f, -115.0f, 40.0f, -90.0f,   0.0f, -90.0f,   0.0f, -90.0f,   0.0f),
                AnimationModelKeyframe(0.5f,  -115.0f,  0.0f, -75.0f,   0.0f, -75.0f,   0.0f, -95.0f, -25.0f),
                AnimationModelKeyframe(0.75f, -90.0f,   0.0f, -115.0f, 40.0f, -90.0f,   0.0f, -90.0f,   0.0f)
        };
