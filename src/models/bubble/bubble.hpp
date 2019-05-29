#include "../model.hpp"
#include "../models.hpp"

class Bubbles{
    int texture;
    std :: vector<vcl :: mesh_drawable> bubbles;
    public:
        Bubbles(int n);
        void update();
        void draw(scene_structure& scene,std::map<std::string,GLuint>& shaders);
};