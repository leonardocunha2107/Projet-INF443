
#include "example_animated_hierarchy.hpp"


#ifdef INF443_EXAMPLE_ANIMATED_HIERARCHY


using namespace vcl;

mesh eclipsoid(float rx,float ry,float rz, const vec3& p0={0,0,0}, size_t Nu=100, size_t Nv=100);


void scene_exercise::setup_data(std::map<std::string,GLuint>& , scene_structure& , gui_structure& )
{
    const float r_head = 0.10f;
    const float a_body = 0.3f;
    const float l=a_body/3;
    const float r_beak=0.05f;

    mesh body = eclipsoid(a_body/3,a_body/3,a_body);
    mesh head=mesh_primitive_sphere(r_head,{0,0,0},20,20);
    mesh_drawable eye = mesh_primitive_sphere(0.05f,{0,0,0},20,20);
    eye.uniform_parameter.color = {0,0,0};

   
    mesh wing_base = mesh_primitive_quad({0,0,0},{l,0,0},{l,l,0},{0,l,0});
    mesh wing_tip = mesh_primitive_quad({0,l/4,0},{l,0,0},{l,l,0},{0,3/4*l,0});
    
    mesh_drawable beak=mesh_primitive_cone(r_beak,{0,0,3*r_beak});
    beak.uniform_parameter.color={0.854, 0.517, 0.062};
    
    
    hierarchy.add_element(body, "body", "root");
    hierarchy.add_element(head,"head","body",{0,0,a_body});
    hierarchy.add_element(eye, "eye_left", "head",{r_head/3,r_head/2,r_head/1.5f});
    hierarchy.add_element(eye, "eye_right", "head",{-r_head/3,r_head/2,r_head/1.5f});

    hierarchy.add_element(wing_base, "wing_base_left", "body",{-a_body/3,0,0});
    hierarchy.add_element(wing_base, "wing_base_right", "body",{a_body/3,0,0});

    hierarchy.add_element(wing_tip, "wing_tip_left", "wing_base_left",{-l,0,0});
    hierarchy.add_element(wing_tip, "wing_tip_right", "wing_base_right",{l,0,0});


    timer.scale = 0.5f;
}


mesh eclipsoid(float rx,float ry,float rz, const vec3& p0, size_t Nu, size_t Nv)
{
    mesh shape;
    for( size_t ku=0; ku<Nu; ++ku ) {
        for( size_t kv=0; kv<Nv; ++kv ) {

            const float u = static_cast<float>(ku)/static_cast<float>(Nu-1);
            const float v = static_cast<float>(kv)/static_cast<float>(Nv);

            const float theta = static_cast<float>( 3.14159f*u );
            const float phi   = static_cast<float>( 2*3.14159f*v );

            const float x = rx * std::sin(theta) * std::cos(phi);
            const float y = ry * std::sin(theta) * std::sin(phi);
            const float z = rz * std::cos(theta);

            const vec3 p = {x,y,z};
            const vec3 n = normalize(p);

            shape.position.push_back( p+p0 );
            shape.normal.push_back( n );
        }
    }

    shape.connectivity = connectivity_grid(Nu, Nv, false, true);

    return shape;
}

void scene_exercise::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{
    timer.update();
    set_gui();

    const float t = timer.t;

    hierarchy.translation("body") = {0,0,0.2f*(1+std::sin(2*3.14f*t))};

    /*hierarchy.rotation("arm_top_left") = rotation_from_axis_angle_mat3({0,1,0}, std::sin(2*3.14f*(t-0.4f)) );
    hierarchy.rotation("arm_bottom_left") = rotation_from_axis_angle_mat3({0,1,0}, std::sin(2*3.14f*(t-0.6f)) );

    hierarchy.rotation("arm_top_right") = rotation_from_axis_angle_mat3({0,-1,0}, std::sin(2*3.14f*(t-0.4f)) );
    hierarchy.rotation("arm_bottom_right") = rotation_from_axis_angle_mat3({0,-1,0}, std::sin(2*3.14f*(t-0.6f)) );*/

    hierarchy.draw(shaders["mesh"], scene.camera);
    if(gui_scene.wireframe)
        hierarchy.draw(shaders["wireframe"], scene.camera);

}




void scene_exercise::set_gui()
{
    ImGui::SliderFloat("Time", &timer.t, timer.t_min, timer.t_max);

    const float time_scale_min = 0.1f;
    const float time_scale_max = 3.0f;
    ImGui::SliderFloat("Time scale", &timer.scale, time_scale_min, time_scale_max);
    ImGui::Checkbox("Wireframe", &gui_scene.wireframe);

}



#endif

