#pragma once
#include "../vcl/vcl.hpp"


class Model{
    public:
        static bool bob_has_ball;
        virtual void update(float t)=0;
        
};

    