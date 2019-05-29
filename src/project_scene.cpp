
#include "project_scene.hpp"
#include <stdio.h>



// Add vcl namespace within the current one - Allows to use function from vcl library without explicitely preceeding their name with vcl::
using namespace vcl;




float evaluate_terrain_z(float u, float v);
vec3 evaluate_terrain(float u, float v);
mesh create_terrain();


/** This function is called before the beginning of the animation loop
    It is used to initialize all part-specific data */
void scene_exercise::setup_data(std::map<std::string,GLuint>& , scene_structure& scene, gui_structure& )
{
    // Create visual terrain surface
    terrain = create_terrain();
    //terrain.uniform_parameter.color = {0.6f,0.85f,0.5f};
    terrain.uniform_parameter.shading.specular = 0.0f; // non-specular terrain material
    terrain.uniform_parameter.scaling=2.0f;
    sand_texture=texture_gpu( image_load_png("data/sand.png") );
    bob_texture=texture_gpu(image_load_png("data/SpongeFace1.png"));
    // Setup initial camera mode and position
    scene.camera.camera_type = camera_control_spherical_coordinates;
    scene.camera.scale = 10.0f;
    scene.camera.apply_rotation(0,0,0,1.2f);
    m=new Models();
    timer.scale = 0.5f;

    skybox = create_skybox();
    skybox.uniform_parameter.shading = {1,0,0};
    skybox.uniform_parameter.rotation = rotation_from_axis_angle_mat3({1,0,0},-3.014f/2.0f);
    texture_skybox = texture_gpu(image_load_png("data/bikiniBottomBox.png"));

    m->bob_->bob_.mesh_visual("head").uniform_parameter.shading.ambiant=1;
    house_=house_bob();
    house_.translation("house")={-10,-15,0.75};
    house_.rotation("head") = rotation_from_axis_angle_mat3({0,0,1},3.014f/2.0f);

    bubs= new Bubbles(100);
    

}



/** This function is called at each frame of the animation loop.
    It is used to compute time-varying argument and perform data data drawing */
void scene_exercise::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{
    set_gui();
    timer.update();
    glEnable( GL_POLYGON_OFFSET_FILL ); // avoids z-fighting when displaying wireframe
    const float t =timer.t;
    m->update(t);
    glBindTexture(GL_TEXTURE_2D, bob_texture);
    glPolygonOffset( 1.0, 1.0 );
     m->bob_->bob_.draw(shaders["mesh"], scene.camera);
    glBindTexture(GL_TEXTURE_2D, scene.texture_white);
    house_.draw(shaders["mesh"], scene.camera);
    m->ball_->ball.draw(shaders["mesh"], scene.camera);
    m->gary_->gary.draw(shaders["mesh"], scene.camera);
       

    glBindTexture(GL_TEXTURE_2D, sand_texture);
    terrain.draw(shaders["mesh"], scene.camera);
    glBindTexture(GL_TEXTURE_2D,texture_skybox);
    skybox.uniform_parameter.scaling = 50.0f;
    skybox.uniform_parameter.translation = scene.camera.camera_position() + vec3(0,0,-10.0f);
    skybox.draw(shaders["mesh"], scene.camera);

    glBindTexture(GL_TEXTURE_2D,scene.texture_white);
    
    if( gui_scene.wireframe ){ // wireframe if asked from the GUI
        glPolygonOffset( 1.0, 1.0 );
        terrain.draw(shaders["wireframe"], scene.camera);
    }
    bubs->update();
    bubs->draw(scene,shaders); 

    

}





// Evaluate 3D position of the terrain for any (u,v) \in [0,1]
vec3 evaluate_terrain(float u, float v)
{
    const float x = 20*(u-0.5f);
    const float y = 20*(v-0.5f);
    const float z = FLOOR/2;

    return {x,y,z};
}

// Generate terrain mesh
mesh create_terrain()
{
    // Number of samples of the terrain is N x N
    const size_t N = 100;

    mesh terrain; // temporary terrain storage (CPU only)
    terrain.position.resize(N*N);
    terrain.texture_uv.resize(N*N);
    // Fill terrain geometry
    for(size_t ku=0; ku<N; ++ku)
    {
        for(size_t kv=0; kv<N; ++kv)
        {
            // Compute local parametric coordinates (u,v) \in [0,1]
            const float u = ku/(N-1.0f);
            const float v = kv/(N-1.0f);

            // Compute coordinates
            terrain.position[kv+N*ku] = evaluate_terrain(u,v);
            terrain.texture_uv[kv+N*ku]={u,v};
        }
    }


    // Generate triangle organization
    //  Parametric surface with uniform grid sampling: generate 2 triangles for each grid cell
    const unsigned int Ns = N;
    for(unsigned int ku=0; ku<Ns-1; ++ku)
    {
        for(unsigned int kv=0; kv<Ns-1; ++kv)
        {
            const unsigned int idx = kv + N*ku; // current vertex offset

            const index3 triangle_1 = {idx, idx+1+Ns, idx+1};
            const index3 triangle_2 = {idx, idx+Ns, idx+1+Ns};

            terrain.connectivity.push_back(triangle_1);
            terrain.connectivity.push_back(triangle_2);
            
        }
    }

    return terrain;
}





void scene_exercise::set_gui()
{
    ImGui::Checkbox("Wireframe", &gui_scene.wireframe);
}


mesh scene_exercise:: create_skybox()
{
    const vec3 p000 = {-1,-1,-1};
    const vec3 p001 = {-1,-1, 1};
    const vec3 p010 = {-1, 1,-1};
    const vec3 p011 = {-1, 1, 1};
    const vec3 p100 = { 1,-1,-1};
    const vec3 p101 = { 1,-1, 1};
    const vec3 p110 = { 1, 1,-1};
    const vec3 p111 = { 1, 1, 1};

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

    const float e = 1e-3f;
    const float u0 = 0.0f;
    const float u1 = 0.25f+e;
    const float u2 = 0.5f-e;
    const float u3 = 0.75f-e;
    const float u4 = 1.0f;
    const float v0 = 0.0f;
    const float v1 = 1.0f/3.0f+e;
    const float v2 = 2.0f/3.0f-e;
    const float v3 = 1.0f;
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


