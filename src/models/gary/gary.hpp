#include "../model.hpp"


class Gary : public Model{
    float t_;
    public:
        void update(float t);
        vcl :: vec3 x;
        vcl :: vec3 x0;
        vcl :: vec3 v;
        vcl :: mesh_drawable_hierarchy gary;
        Gary();
};