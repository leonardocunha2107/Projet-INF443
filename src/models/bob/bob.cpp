#include "../../vcl/vcl.hpp"
#include "../models.hpp"
#include <math.h>
using namespace vcl;
using namespace std;

/*mesh body(float c, float b, float a){
    mesh head = mesh_primitive_parallelepiped({-a/2,-b/2,-c/2},{a,0,0},{0,b,0},{0,0,c});
    head.texture_uv.resize(16);
    a=a/(3*a+2*c);
    b=b/(3*b+2*c);
    float cx=c/(3*a+2*c);
    float cy = c/(3*b+2*c);
    head.texture_uv={{a+cx,b+cy},{2*a+cx,b+cy},{a+cx,2*b+cy},{a,b},
                        {2*a+cx,2*b+cy},{2*a+cx,b},{a+cx,0},{2*a+cx,0},
                        {a+cx,b+cy},{2*a+cx,b+cy},{a+cx,2*b+cy},{a,b},
                        {2*a+cx,2*b+cy},{2*a+cx,b},{a+cx,0},{2*a+cx,0}};
    /*head.texture_uv={{0,0},{1,0},{0,1},{0,0},
                    {1,1},{0,1},{1,1},{0,1},
                    {0,0},{1,0},{0,1},{0,0},
                        {1,1},{0,1},{1,1},{0,1}};    
                                    
    return head;
}*/

mesh body(float c,float b ,float a){
    vec3 p0={-a/2,-b/2,-c/2};
    vec3 t1={a,0,0};
    vec3 t2={0,b,0};
    vec3 t3={0,0,c};
    const vec3 p000 = p0;
    const vec3 p100 = p0+t1;
    const vec3 p010 = p0+t2;
    const vec3 p001 = p0+t3;
    const vec3 p110 = p0+t1+t2;
    const vec3 p101 = p0+t1+t3;
    const vec3 p011 = p0+t2+t3;
    const vec3 p111 = p0+t1+t2+t3;
    mesh skybox;

    skybox.position = {
        p000, p100, p110, p010,
        p010, p110, p111, p011,
        p100, p110, p111, p101,
        p000, p001, p010, p011,
        p001, p101, p111, p011,
        p000, p100, p101, p001
    };


    skybox.connectivity = {
        {0,1,2}, {0,2,3}, {4,5,6}, {4,6,7},
        {8,11,10}, {8,10,9}, {17,16,19}, {17,19,18},
        {23,22,21}, {23,21,20}, {13,12,14}, {13,14,15}
    };

    a=a/(3*a+2*c);
    b=b/(3*b+2*c);
    float cx=c/(3*a+2*c);
    float cy = c/(3*b+2*c);
    const float e = 1e-3f;
    const float u0 = 0.0f;
    const float u1 = a+cx-0.1;
    const float u2 = 2*a+cx-e;
    const float u3 = 0.75f-e;
    const float u4 = 1.0f;
    const float v0 = 1.0f;
    const float v1 = 2.0f/3.0f+e;
    const float v2 = 1.0f/3.0f-e;
    const float v3 = 0.0f;
    skybox.texture_uv = {
        {u1,v1}, {u2,v1}, {u2,v2}, {u1,v2},
        {u1,v2}, {u2,v2}, {u2,v3}, {u1,v3},
        {u2,v1}, {u2,v2}, {u3,v2}, {u3,v1},
        {u1,v1}, {u0,v1}, {u1,v2}, {u0,v2},
        {u4,v1}, {u3,v1}, {u3,v2}, {u4,v2},
        {u1,v1}, {u2,v1}, {u2,v0}, {u1,v0}
    };


    return skybox;

}


mesh_drawable_hierarchy spongebob(){

    mesh_drawable_hierarchy bob;
    float width=0.5;
    float height=0.65 ;
    float deep=0.2;
    float arm_length=0.4;
    float leg_length=0.3;
    float hand_radius=0.08;
    mesh head = body(deep,height,width);
    vec3 arm_axis={arm_length*sin(3.14/4),-arm_length*sin(3.14/4),0};
    mesh_drawable left_arm = mesh_primitive_cylinder(deep/5,{0,0,0},{-arm_length,0,0});
    left_arm.uniform_parameter.color={255,255,0};
    mesh_drawable right_arm = mesh_primitive_cylinder(deep/5,{0,0,0},arm_axis);
    right_arm.uniform_parameter.color={255,255,0};


    mesh_drawable leg = mesh_primitive_cylinder(deep/5,{0,0,0},{0,-leg_length,0});
    leg.uniform_parameter.color={255,255,0};
    mesh_drawable hand = mesh_primitive_sphere(hand_radius);
    hand.uniform_parameter.color={255,255,0};
    mesh_drawable feet = mesh_primitive_parallelepiped({-deep/4,-deep/4,-deep/2},{deep/2,0,0},{0,deep/2,0},{0,0,deep});
    feet.uniform_parameter.color={0,0,0};

    bob.add_element(head,"head","root");
    bob.add_element(left_arm,"left arm","head",{-width/2+0.05,0,0});
    bob.add_element(right_arm,"right arm","head",{width/2-0.05,0,0});
    bob.add_element(hand,"left_ hand","left arm",{-arm_length,0,0});
    bob.add_element(hand,"right hand","right arm",arm_axis);
    bob.add_element(leg,"left leg","head",{-width/4,-height/2,0});
    bob.add_element(leg,"right leg","head",{width/4,-height/2,0});
    bob.add_element(feet,"left foot","left leg",{0,-leg_length-deep/4,0});
    bob.add_element(feet,"right foot","right leg",{0,-leg_length-deep/4,0});
    
    //rotations
    bob.rotation("head")={1 ,0,0,
                          0,0,-1,
                          0,1,0};
    float y=3.14/4;
    bob.rotation("left arm")=rotation_from_axis_angle_mat3({0,0,1},y);
    return bob;
}



Bob :: Bob(){

    bob_=spongebob();
    
}

void Bob ::update(float t){
    float pi2=6.28;
    float z=3.14/4;
    float x= pi2*t_/2;
    if(Models ::s==0)
    {
        bob_.rotation("right arm")=rotation_from_axis_angle_mat3({1,0,0},-x);
        if(abs(fmod(x,pi2)-3.14)<0.1)
            Models :: ball_->random_v();
        t_=t;
   
    }
    else if(abs(fmod(x,pi2))>0.2){
        bob_.rotation("right arm")=rotation_from_axis_angle_mat3({1,0,0},-x);
        t_=t;
    }
    
    
}

mat3 dot(mat3 a, mat3 b){
    mat3 res;
    for(int i=0;i<3;i++)
        for(int j=0; j<3; j++)
            for(int k=0;k<3;k++)
                res;
    return res;

}


    
    

