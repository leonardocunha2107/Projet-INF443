#include "house.hpp"

using namespace vcl;



mesh create_cone(float radius, float height, float offset)
{
    // Number of samples of the cylinder is N x N
    const size_t N = 20;

    mesh cone; // temporary Cylinder storage (CPU only)
    cone.position.resize(N+2);
    // Fill Cylinder geometry
    for(size_t ku=0; ku<N; ++ku)
    {
        //parameter
        const float u = ku/(N-1.0f);
    //compute the coordinates
        const float x = std::cos(2*3.14f*u)*radius;
        const float y = std::sin(2*3.14f*u)*radius;
        cone.position[ku]= {x,y,offset+height};
        cone.position[N]= {0.0f,0.0f,offset};
        cone.position[N+1]= {0.0f,0.0f,offset};
    }

    // Generate triangle organization
    //  Parametric surface with uniform grid sampling: generate 2 triangles for each grid cell
    const unsigned int Ns = N;
    for(unsigned int ku=0; ku<Ns; ++ku)
    {
        const unsigned int idx = ku; // current vertex offset

        const index3 triangle_1 = {idx, N+1, (idx+1)%Ns};
        const index3 triangle_2 = {idx, N, (idx+1)%Ns};

        cone.connectivity.push_back(triangle_1);
        cone.connectivity.push_back(triangle_2);
    }

    return cone;
}

 mesh_drawable_hierarchy house_bob(){
        //house stuff
    const float scale=1.0f;
    const float height_house = 3.0f*scale;
    const float house_width = 2.0f*scale;
    const float foliage_height=1.0f*scale;
    const float window_radius=0.3f*scale;

    const mat3 R1_foliage = rotation_from_axis_angle_mat3({0,1,1}, 3.14f/3.0f);
    const mat3 R2_foliage = rotation_from_axis_angle_mat3({0,0,1}, 3.14f*2/3.0f);


    mesh_drawable house = eclipsoid(house_width, house_width,height_house,{0.0f,0.0f,0.0f},20,20);
    house.uniform_parameter.color={1.0f, 0.7f, 0.0f};

    mesh foliage = create_cone(0.3f*scale,foliage_height,0.0f);
    foliage.push_back(create_cone(0.3f*scale,foliage_height,foliage_height/3.0f));
    foliage.push_back(create_cone(0.3f*scale,foliage_height,foliage_height*2/3.0f));
    mesh_drawable foliageD= mesh_drawable(foliage);
    foliageD.uniform_parameter.color={0.05f, 0.8f, 0.05f};

    mesh window = mesh_primitive_cylinder(window_radius,{2.0f*scale,0,0},{0,0,0});
    window.push_back(mesh_primitive_disc(window_radius,{2.0f*scale,0,0},{1,0,0},40));
    mesh_drawable windowD= mesh_drawable(window);
    windowD.uniform_parameter.color={0.3f, 0.8f, 0.9f};



    mesh_drawable door = mesh_primitive_parallelepiped({0.0f,0.0f,0.0f},{0.0f,house_width/2.0f,0.0f},{house_width,0.0f,0.0f},{0.0f,0.0f,-height_house/2.0f});
    door.uniform_parameter.color={0.8f, 0.8f, 0.8f};

    mesh_drawable_hierarchy hierarchy;
    hierarchy.add_element(house, "house", "root");
    hierarchy.add_element(foliageD, "foliage0", "house", {0,0,height_house-foliage_height*2/3.0f});
    hierarchy.add_element(foliageD, "foliage1", "house", {0,0,height_house-foliage_height*2/3.0f},R1_foliage);
    hierarchy.add_element(foliageD, "foliage2", "house", {0,0,height_house-foliage_height*2/3.0f}, R2_foliage*R1_foliage);
    hierarchy.add_element(foliageD, "foliage3", "house", {0,0,height_house-foliage_height*2/3.0f}, R2_foliage*R2_foliage*R1_foliage);
    hierarchy.add_element(windowD, "window1", "house", {-0.2f,house_width/3.0f, height_house/2.0f});
    hierarchy.add_element(windowD, "window2", "house", {-0.1f,-house_width/3.0f, height_house/3.0f});
    hierarchy.add_element(door, "door", "house", {0.0f,-house_width/4.0f, 0.0f});
    //end house stuff
}
