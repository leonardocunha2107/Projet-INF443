#pragma once
#include "bob/bob.hpp"
#include "ball/ball.hpp"
class Models{
    public:
        static bool bob_has_ball;
        static Bob* bob_;
        static Ball* ball_;
        Models();
        void update(float t);
};