#include "../../vcl/vcl.hpp"
#include "bob.hpp"
#include <math.h>
//#include "bob.hpp"
using namespace vcl;
using namespace std;

mesh body(float c, float b, float a){
    mesh head = mesh_primitive_parallelepiped({-a/2,-b/2,-c/2},{a,0,0},{0,b,0},{0,0,c});
    head.texture_uv.resize(16);
    a=a/(3*a+2*c);
    b=b/(3*b+2*c);
    float cx=c/(3*a+2*c);
    float cy = c/(3*b+2*c);
    /*head.texture_uv={{a+cx,b+cy},{2*a+cx,b+cy},{a+cx,2*b+cy},{a,b},
                        {2*a+cx,2*b+cy},{2*a+cx,b},{a+cx,0},{2*a+cx,0},
                        {a+cx,b+cy},{2*a+cx,b+cy},{a+cx,2*b+cy},{a,b},
                        {2*a+cx,2*b+cy},{2*a+cx,b},{a+cx,0},{2*a+cx,0}};*/
    /*head.texture_uv={{0,0},{1,0},{0,1},{0,0},
                    {1,1},{0,1},{1,1},{0,1},
                    {0,0},{1,0},{0,1},{0,0},
                        {1,1},{0,1},{1,1},{0,1}};    */
                                    
    return head;
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
    float x= -pi2*t;

    
    bob_.rotation("right arm")=rotation_from_axis_angle_mat3({1,0,0},x);
}

mat3 dot(mat3 a, mat3 b){
    mat3 res;
    for(int i=0;i<3;i++)
        for(int j=0; j<3; j++)
            for(int k=0;k<3;k++)
                res;
    return res;

}


    
    

