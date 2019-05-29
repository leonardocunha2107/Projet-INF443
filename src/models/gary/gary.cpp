#include <time.h> 
#include <stdlib.h> 
#include <stdio.h>
#include "../models.hpp"
#include <math.h>
using namespace vcl;

void Gary :: update(float t){
    if(Models :: s==2){
         v =Models ::ball_->x-x;
        v.z=0;
        if(norm(v)<0.5)
            Models :: s =3;
        v=normalize(v);

        float angle;
        if(v.x>0) angle=-std::acos(v.y);
        else angle=std::acos(v.y);

        gary.rotation("base")=rotation_from_axis_angle_mat3({0,0,1},angle);
        x=x+(v*0.015);
    }
    if(Models :: s==3){
         v = x0-x;
        v.z=0;
        if(norm(v)<0.5)
            Models :: s =0;
        v=normalize(v);
        float angle;
        if(v.x>0) angle=-std::acos(v.y);
        else angle=std::acos(v.y);


        gary.rotation("base")=rotation_from_axis_angle_mat3({0,0,1},angle);
        x=x+(v*0.015);
    }
    gary.translation("base") =x;
}

 Gary :: Gary(){
    
    const float scale=0.5f;
    const float body_width = 0.5f*scale;
    const float body_radius = 0.6f*scale;
    const float antenna_height=1.0f*scale;
    const float antenna_radius = 0.03f*scale;
    const float eye_radius = 0.1f*scale;
    const float base_length=1.0f*scale;
    const float base_width=0.4f*scale;
    const float base_height=0.3f*scale;


    const mat3 R1_foliage = rotation_from_axis_angle_mat3({0,1,1}, 3.14f/6.0f);
    const mat3 R2_foliage = rotation_from_axis_angle_mat3({0,0,1}, 3.14f*2/3.0f);

    mesh_drawable base = mesh_primitive_parallelepiped({0.0f,0.0f,FLOOR},{base_width,0.0f,0.0f},{0.0f,base_length,0.0f},{0.0f,0.0f,base_height});
    base.uniform_parameter.color={0.2f,0.7f, 0.8f};

    mesh body = mesh_primitive_cylinder(body_radius,{body_width,0,0},{0,0,0});
    body.push_back(mesh_primitive_disc(body_radius,{0.01f,0,0},{0,0,0},20));
    body.push_back(mesh_primitive_disc(body_radius,{body_width-0.01f,0,0},{0,0,0},20));
    mesh_drawable bodyD= mesh_drawable(body);
    bodyD.uniform_parameter.color={0.9f, 0.5f, 0.5f};

    mesh_drawable antenna = mesh_primitive_cylinder(antenna_radius,{0,0,0},{0,0,antenna_height});
    antenna.uniform_parameter.color={1.0f, 0.8f, 0.8f};

    mesh_drawable eye = mesh_primitive_sphere(eye_radius,{0,0,antenna_height});
    eye.uniform_parameter.color={0.8f, 1.0f, 0.8f};

    gary.add_element(base, "base", "root");
    gary.add_element(bodyD, "body","base",{-0.05f,base_length/3, -body_radius+  base_height/5});
    gary.add_element(antenna, "antenna1","base",{2*base_width/3,base_length*0.9f, -antenna_height-base_height/5},R1_foliage);
    gary.add_element(antenna, "antenna2","base",{base_width/3,base_length*0.9f, -antenna_height-base_height/5},R2_foliage*R1_foliage);
    gary.add_element(eye, "eye1","antenna1",{0,0,0});
    gary.add_element(eye, "eye2","antenna2",{0,0,0});
    x=Models ::bob_->bob_.translation("head")+vec3({0,0.25,0});;
    gary.translation("base") =x;
    x0=x;
    v={0,0,0};
}   