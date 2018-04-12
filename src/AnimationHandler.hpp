
#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "objects/Horse.hpp"



//---------------------------------------------------------
// Types
//---------------------------------------------------------

struct AnimationModelKeyframe
{
    AnimationModelKeyframe()
    {
        frLegTopRot = -90.0f;
        frLegBotRot = 0.0f;
        flLegTopRot = -90.0f;
        flLegBotRot = 0.0f;
        brLegTopRot = -90.0f;
        brLegBotRot = 0.0f;
        blLegTopRot = -90.0f;
        blLegBotRot = 0.0f;
        neckRot = 115.0f;
        tailRot = -80.0f;
    }
    AnimationModelKeyframe(float frameLength,
                           float frLegTopRot,
                           float frLegBotRot,
                           float flLegTopRot,
                           float flLegBotRot,
                           float brLegTopRot,
                           float brLegBotRot,
                           float blLegTopRot,
                           float blLegBotRot,
                           float neckRot,
                           float tailRot);

    float frameTime;
    float frLegTopRot;
    float frLegBotRot;
    float flLegTopRot;
    float flLegBotRot;
    float brLegTopRot;
    float brLegBotRot;
    float blLegTopRot;
    float blLegBotRot;
    float neckRot;
    float tailRot;
};


enum class AnimationType
{
    IDLE,
    WALK,
    RUN,
    TURN
};

enum class MovementPhase
{
    WALKING,
    TURNING
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

    //Movement
    bool isColliding = false;
    bool isChosenToMove = false;
    float movementTimeCounter = 0.0f;
    float movementLength = 0.0f;
    float movementSpeed = 0.0f;
};

struct MovementState
{
    bool isAnimating = true;
    bool isColliding = false;
    bool isChosenToMove = false;
    float timeCounter = 0.0f;
    float movementLength = 0.0f;
    float movementSpeed = 0.0f;
    MovementPhase movementPhase = MovementPhase::WALKING;
};


class AnimationHandler
{

public:

    explicit AnimationHandler(std::vector<std::shared_ptr<Horse>> horses);

    void enableAnimations(bool value);
    void setAnimationType(AnimationType type);
    void setAnimationType(AnimationType type, AnimationState &state);

    void tick(float deltaTime);



private:


    //Degrees/second for rotation.
    const float RotateSpeed = 15;
    const float RotateAnimDuration = 1.0f;
    const float HorseRadius = 1.0f;

    const std::vector<AnimationModelKeyframe> HorseIdleModelAnim
            {
                    AnimationModelKeyframe()
            };

    const std::vector<AnimationModelKeyframe> HorseWalkModelAnim
            {
                    //                     time  frt      frb    flt       flb   brt     brb     btl       blb   neck  tail
                    AnimationModelKeyframe(0.0f, -75.0f,   0.0f, -115.0f,  0.0f, -95.0f, -25.0f, -75.0f,   0.0f, 115.0f, -80.0f),
                    AnimationModelKeyframe(0.5f, -115.0f, 40.0f, -90.0f,   0.0f, -90.0f,   0.0f, -90.0f,   0.0f, 125.0f, -90.0f),
                    AnimationModelKeyframe(1.0f, -115.0f,  0.0f, -75.0f,   0.0f, -75.0f,   0.0f, -95.0f, -25.0f, 115.0f, -80.0f),
                    AnimationModelKeyframe(1.5f, -90.0f,   0.0f, -115.0f, 40.0f, -90.0f,   0.0f, -90.0f,   0.0f, 105.0f, -70.0f),
                    AnimationModelKeyframe(2.0f, -75.0f,   0.0f, -115.0f,  0.0f, -95.0f, -25.0f, -75.0f,   0.0f, 115.0f, -80.0f),
            };

    const std::vector<AnimationModelKeyframe> HorseRunModelAnim
            {
                    //                     len     frt      frb    flt       flb   brt     brb     btl       blb
                    AnimationModelKeyframe(0.0f,   -75.0f,   0.0f, -115.0f,  0.0f, -95.0f, -25.0f, -75.0f,   0.0f, 115.0f, -80.0f),
                    AnimationModelKeyframe(0.125f, -115.0f, 40.0f, -90.0f,   0.0f, -90.0f,   0.0f, -90.0f,   0.0f, 125.0f, -90.0f),
                    AnimationModelKeyframe(0.25f,  -115.0f,  0.0f, -75.0f,   0.0f, -75.0f,   0.0f, -95.0f, -25.0f, 115.0f, -80.0f),
                    AnimationModelKeyframe(0.375f, -90.0f,   0.0f, -115.0f, 40.0f, -90.0f,   0.0f, -90.0f,   0.0f, 105.0f, -70.0f),
                    AnimationModelKeyframe(0.5f,   -75.0f,   0.0f, -115.0f,  0.0f, -95.0f, -25.0f, -75.0f,   0.0f, 115.0f, -80.0f),
            };

    std::vector<std::shared_ptr<Horse>> _horses;
    std::vector<AnimationState> _horseAnimStates;
    std::vector<MovementState>  _horseMovementStates;

    std::mt19937 _randomGen;
    std::bernoulli_distribution _bernoulli;
    std::uniform_real_distribution<> _speedDistrib;
    std::uniform_real_distribution<> _distanceDistrib;

    void tickModelAnim(float deltaTime);
    void tickIdleAnim(std::shared_ptr<Horse> horse);
    void tickWalkAnim(float deltaTime, std::shared_ptr<Horse> horse, unsigned int& animStateIndex);
    void tickRunAnim(float deltaTime,  std::shared_ptr<Horse> horse, unsigned int& animStateIndex);
    void tickTurnAnim(float deltaTime, std::shared_ptr<Horse> horse, unsigned int& animStateIndex);

    void applyModelKeyFrame(AnimationModelKeyframe keyframe, std::shared_ptr<Horse> horse);
    //ratio: 0.0f = frame 1, 1.0f = frame 2; linear combination
    void applyModelKeyFrame(float ratio, AnimationModelKeyframe keyframe1, AnimationModelKeyframe keyframe2, std::shared_ptr<Horse> horse);

    void tickMovementAnim(float deltaTime);

    void tickCollisionDetect();
    float getDistance(std::shared_ptr<Horse> horse1, std::shared_ptr<Horse> horse2);

};
