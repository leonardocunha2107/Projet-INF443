
#include "../model.hpp"



class Bob :  public Model {
    public: 
        vcl :: mesh_drawable_hierarchy bob_;
        void update(float t);
        Bob();
};
