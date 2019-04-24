
#include "terrain.cpp"
#include <random>
#include "01_modelisation.hpp"

#ifdef INF443_01_MODELISATION


mesh create_cylinder(float radius, float height);
mesh create_cone(float radius, float height, float z_offset);
mesh create_tree_foliage(float radius, float height, float z_offset,float tree_height);
vec3 evaluate_terrain(float u, float v);
mesh create_tree(float tree_radius, float tree_height);
mesh create_forest(int n_trees);
float evaluate_terrain_z(float u, float v);
vec3 evaluate_terrain(float u, float v);
mesh create_terrain();


// Add vcl namespace within the current one - Allows to use function from vcl library without explicitely preceeding their name with vcl::
using namespace vcl;

mesh create_tree(float tree_radius,float tree_height){
    mesh trunk= create_cylinder(tree_radius,tree_height);
    trunk.fill_color_uniform({0.54f,0.27f,0.07f});
    mesh leaves =create_tree_foliage(3*tree_radius,tree_height,tree_height/5,tree_height);
    leaves.fill_color_uniform({0.0f,1.0f,0.0f});
    mesh tree;
    tree.push_back(leaves);
    tree.push_back(trunk);
    return tree;
}

mesh create_forest(int n_trees=10){
    std::uniform_real_distribution<float> distrib(0.0,1.0);
    std::default_random_engine generator;
    float u;
    float v;
    vec3 tree_position;
    mesh forest;
    for(int i=0;i<n_trees;i++){
        u=distrib(generator);
        v=distrib(generator);
        tree_position=evaluate_terrain(u,v);
        mesh tree=create_tree(0.1,0.5);
        for(int i=0;i<tree.position.size();i++)
            tree.position[i]=tree.position[i]+tree_position;
        forest.push_back(tree);
    }
    return forest;
}
mesh create_grass(int n_grass=10){
    std::uniform_real_distribution<float> distrib(0.0,1.0);
    std::default_random_engine generator;
    generator.seed(2);
    float u;
    float v;
    vec3 grass_position;
    mesh grass;
    mesh roca;
    grass.texture_uv   = {{0,1}, {1,1}, {1,0}, {0,0}};
    grass.connectivity = {{0,1,2}, {0,2,3}};
    for(int i=0;i<n_grass;i++){
        grass.position     = {{-0.2f,0,0}, { 0.2f,0,0}, { 0.2f, 0.4f,0}, {-0.2f, 0.4f,0}};
        u=distrib(generator);
        v=distrib(generator);
        grass_position=evaluate_terrain(u,v);
        for(int i=0;i<grass.position.size();i++)
            grass.position[i]=grass.position[i]+grass_position;
        roca.push_back(grass);
    }
    return roca;
}
mesh create_cylinder(float radius, float height)
{
    mesh m;

    // Number of samples
    const size_t N = 20;

    // Geometry
    for(size_t k=0; k<N; ++k)
    {
        const float u = k/float(N);
        const vec3 p = {radius*std::cos(2*3.14f*u), radius*std::sin(2*3.14f*u), 0.0f};
        m.position.push_back( p );
        m.position.push_back( p+vec3(0,0,height) );
    }

    // Connectivity
    for(size_t k=0; k<N; ++k)
    {
        const unsigned int u00 = 2*k;
        const unsigned int u01 = (2*k+1)%(2*N);
        const unsigned int u10 = (2*(k+1))%(2*N);
        const unsigned int u11 = (2*(k+1)+1) % (2*N);

        const index3 t1 = {u00, u10, u11};
        const index3 t2 = {u00, u11, u01};
        m.connectivity.push_back(t1);
        m.connectivity.push_back(t2);
    }

    return m;
}

mesh create_cone(float radius, float height, float z_offset)
{
    mesh m;

    // conical structure
    // *************************** //

    const size_t N = 20;

    // geometry
    for(size_t k=0; k<N; ++k)
    {
        const float u = k/float(N);
        const vec3 p = {radius*std::cos(2*3.14f*u), radius*std::sin(2*3.14f*u), 0.0f};
        m.position.push_back( p+vec3{0,0,z_offset} );
    }
    // apex
    m.position.push_back({0,0,height+z_offset});

    // connectivity
    const unsigned int Ns = N;
    for(unsigned int k=0; k<Ns; ++k) {
        m.connectivity.push_back( {k , (k+1)%N, Ns} );
    }

    // close the part in the bottom of the cone
    // *************************** //

    // Geometry
    for(size_t k=0; k<N; ++k)
    {
        const float u = k/float(N);
        const vec3 p = {radius*std::cos(2*3.14f*u), radius*std::sin(2*3.14f*u), 0.0f};
        m.position.push_back( p+vec3{0,0,z_offset} );
    }
    // central position
    m.position.push_back( {0,0,z_offset} );

    // connectivity
    for(unsigned int k=0; k<Ns; ++k)
        m.connectivity.push_back( {k+Ns+1, (k+1)%Ns+N+1, 2*Ns+1} );

    return m;
}
mesh create_tree_foliage(float radius, float height, float z_offset,float tree_height)
{
    mesh m;
    mesh cone= create_cone(radius, height, 0);
    for(int i =0; i< cone.position.size();i++)
        cone.position[i][2]+=tree_height;
    m.push_back(cone);
    for(int i =0; i< cone.position.size();i++)
        cone.position[i][2]+=z_offset;
    m.push_back(cone);
    for(int i =0; i< cone.position.size();i++)
        cone.position[i][2]+=z_offset;
    m.push_back(cone);
  

    return m;
}

#endif



