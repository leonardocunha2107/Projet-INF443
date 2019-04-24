
#include "01_modelisation.hpp"
#include "meshes.cpp"

#ifdef INF443_01_MODELISATION

// Add vcl namespace within the current one - Allows to use function from vcl library without explicitely preceeding their name with vcl::
using namespace vcl;









/** This function is called before the beginning of the animation loop
    It is used to initialize all part-specific data */
void scene_exercise::setup_data(std::map<std::string,GLuint>& , scene_structure& scene, gui_structure& )
{
    // Create visual terrain surface
    terrain = create_terrain();
    terrain.uniform_parameter.color = {0.6f,0.85f,0.5f};
    terrain.uniform_parameter.shading.specular = 0.0f; // non-specular terrain material
    texture_field = texture_gpu( image_load_png("data/grass.png") );
    
    //create forest
    forest=create_forest(20);
    grass=create_grass(10);
    texture_grass = texture_gpu( image_load_png("data/billboard_grass.png") );

    // Setup initial camera mode and position
    scene.camera.camera_type = camera_control_spherical_coordinates;
    scene.camera.scale = 10.0f;
    scene.camera.apply_rotation(0,0,0,1.2f);

}



/** This function is called at each frame of the animation loop.
    It is used to compute time-varying argument and perform data data drawing */
void scene_exercise::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{
    set_gui();
    
    
    glEnable( GL_POLYGON_OFFSET_FILL ); // avoids z-fighting when displaying wireframe


    // Display terrain
    glBindTexture(GL_TEXTURE_2D, texture_field);
    glPolygonOffset( 1.0, 1.0 );
    terrain.draw(shaders["mesh"], scene.camera);
    
    //draw trees
    glBindTexture(GL_TEXTURE_2D, scene.texture_white);
    glPolygonOffset( 0,0 );
    forest.draw(shaders["mesh"],scene.camera);

    //draw grass
    glBindTexture(GL_TEXTURE_2D, texture_grass);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // avoids sampling artifacts
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // avoids sampling artifacts
    const mat3 R = rotation_from_axis_angle_mat3({0,1,0}, 3.14f/2.0f); // orthogonal rotation
    grass.uniform_parameter.rotation = R;
    grass.draw(shaders["mesh"], scene.camera);
    
    if( gui_scene.wireframe ){ // wireframe if asked from the GUI
        glPolygonOffset( 1.0, 1.0 );
        terrain.draw(shaders["wireframe"], scene.camera);
    }

}





void scene_exercise::set_gui()
{
    ImGui::Checkbox("Wireframe", &gui_scene.wireframe);
}



#endif

