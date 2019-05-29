#include <time.h> 
#include <stdlib.h> 
#include "../models.hpp"

using namespace vcl;


void Ball :: random_v(){
    srand (time(NULL));
    float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    x=2*x-1;
    v={x,y,z};
    v=3*v;
    Models :: s=1;
}

void Ball :: update(float t){
    if(Models :: s==0)
        x=Models::bob_->bob_.mesh_visual("right hand").uniform_parameter.translation+vec3({0.12,0,0});
    if(Models :: s==1){
        if(x.z-FLOOR<0.09){
        Models :: s=4;
        v.z=-v.z*0.8;
        x.z=FLOOR+0.1;
        }
        else{
        v=v-(3*vec3({0,0,1})*(t-t_));
        x=x+v*(t-t_);
        }
    }
    if(Models :: s==4){
        if(x.z-FLOOR<0.09)
            Models :: s=2;

        else{
            v=v-(3*vec3({0,0,1})*(t-t_));
            x=x+v*(t-t_);
        }
    }

    if(Models :: s ==3)
        x=Models :: gary_->x+vec3({0,0,FLOOR+0.2})+(0.5*normalize(Models :: gary_->v));

     t_=t;
     ball.uniform_parameter.translation=x;
    

}

Ball :: Ball(){
    ball=mesh_primitive_sphere(0.12);
    ball.uniform_parameter.color={200,0,0};
    t_=0;
}