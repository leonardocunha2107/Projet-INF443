#pragma once
#include "bob/bob.hpp"
#include "ball/ball.hpp"
#include "gary/gary.hpp"
#include "../tool/base_exercise.hpp"

#define FLOOR -0.7
class Models{
    public:
        static int s;
        //s refers to animation state
        //0 for bob has ball
        //1 for ball flying
        //2 for ball in the ground
        //3 for ball with gary
        static Bob* bob_;
        static Ball* ball_;
        static Gary* gary_;
        Models();
        void update(float t);
};