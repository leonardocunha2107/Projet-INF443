#include "bubble.hpp"
#include <time.h> 
#include <stdlib.h> 
using namespace vcl;

Bubbles :: Bubbles(int n){
    srand (time(NULL));
    float x,y,z;
    bubbles=std::vector<mesh_drawable>(n);
    mesh m;
    m.position     = {{-0.2f,0,0}, { 0.2f,0,0}, { 0.2f, 0.4f,0}, {-0.2f, 0.4f,0}};
    m.texture_uv   = {{0,1}, {1,1}, {1,0}, {0,0}};
    m.connectivity = {{0,1,2}, {0,2,3}};

    for(int i=0;i<n;i++){
        x = 20*(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)-0.5);
        y = 20*(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)-0.5);
        z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        bubbles[i]=mesh_drawable(m);
        bubbles[i].uniform_parameter.translation={x,y,z};//{-20,-20,FLOOR};
        bubbles[i].uniform_parameter.shading = {1,0,0};
    }
    texture=texture_gpu( image_load_png("data/bubble.png") );
}


void Bubbles :: draw(scene_structure& scene,std::map<std::string,GLuint>& shaders){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(false);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // avoids sampling artifacts
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    for(int i=0;i<bubbles.size();i++){
        bubbles[i].uniform_parameter.rotation = scene.camera.orientation;
        bubbles[i].draw(shaders["mesh"], scene.camera);
    }
    glBindTexture(GL_TEXTURE_2D, scene.texture_white);
    glDepthMask(true);
}

void Bubbles :: update(){
    srand (time(NULL));
    float x,y,z;
    for(int i=0;i<bubbles.size();i++){
         x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)-0.5;
         y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)-0.5;
         z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)-0.0;
         bubbles[i].uniform_parameter.translation+=0.01*vec3{x,y,z};
    }
}