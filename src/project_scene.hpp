#pragma once

#include "tool/base_exercise.hpp"
#include "models/models.hpp"
#include "models/house/house.hpp"
#include "models/bubble/bubble.hpp"
// Stores some parameters that can be set from the GUI
struct gui_scene_structure
{
    bool wireframe;
};

struct scene_exercise : base_scene_exercise
{

    /** A part must define two functions that are called from the main function:
     * setup_data: called once to setup data before starting the animation loop
     * frame_draw: called at every displayed frame within the animation loop
     *
     * These two functions receive the following parameters
     * - shaders: A set of shaders.
     * - scene: Contains general common object to define the 3D scene. Contains in particular the camera.
     * - data: The part-specific data structure defined previously
     * - gui: The GUI structure allowing to create/display buttons to interact with the scene.
    */

    void setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    void frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    Models* m;
    Bubbles* bubs;
    void set_gui();

    // visual representation of a surface
    vcl::mesh_drawable terrain;
    vcl::timer_event timer;
    gui_scene_structure gui_scene;
    int sand_texture;
    int bob_texture;
    int texture_skybox;
    int texture_patrick;
    vcl::mesh create_skybox();
    vcl :: mesh_drawable skybox;
    vcl::mesh_drawable_hierarchy house_;
    vcl::mesh_drawable surface_bubble;
    vcl ::mesh_drawable patrick_house;
};



