#include <time.h> 
#include <stdlib.h> 
#include <stdio.h>
#include "../models.hpp"

using namespace vcl;

void Gary :: update(float t){
    if(Models :: s==2){
        vec3 v =Models ::ball_->x-x;
        v.z=0;
        
        if(norm(v)<0.5)
            Models :: s =3;
        v=normalize(v);
        x=x+(v*0.015);
    }
    if(Models :: s==3){
        vec3 v = x0-x;
        v.z=0;
        if(norm(v)<0.5)
            Models :: s =0;
        v=normalize(v);
        x=x+(v*0.015);
    }
    gary.uniform_parameter.translation =x;
}

 Gary :: Gary(){
    //TODO
    gary=mesh_primitive_parallelepiped({0,0,FLOOR},{0.2,0,0},{0,0.2,0},{0,0,0.2});
    x=Models ::bob_->bob_.mesh_visual("head").uniform_parameter.translation;
    gary.uniform_parameter.translation =x;
    x0=x;
}