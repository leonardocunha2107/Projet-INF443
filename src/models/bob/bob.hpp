
#include "../model.hpp"



class Bob :  public Model {
    float t_;
    public: 
        vcl :: mesh_drawable_hierarchy bob_;
        void update(float t);
        Bob();
};
