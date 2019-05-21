#include <time.h> 
#include <stdlib.h> 
#include "../models.hpp"

using namespace vcl;


void Ball :: random_v(){
    srand (time(NULL));
    float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    v={x,y,z};
}

void Ball :: update(float t){
    if(Models :: bob_has_ball){
        ball.uniform_parameter.translation=Models::bob_->bob_.mesh_visual("right hand").uniform_parameter.translation+vec3({0.12,0,0});
    }
    
    

}

Ball :: Ball(){
    ball=mesh_primitive_sphere(0.12);
    ball.uniform_parameter.color={200,0,0};
}