#include "../model.hpp"


class Ball : public Model{
    public:
        vcl :: vec3 v;
        vcl :: vec3 x;
        void random_v();
        vcl :: mesh_drawable ball;
        void update(float t);
        Ball();
};