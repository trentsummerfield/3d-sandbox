#include "App.h"
#include "Loader.h"
#include "Grid.h"

App::App(std::shared_ptr<ShaderManager> shader_manager, ShaderHandle shader)
  : shader_manager{ shader_manager }
  , grid{ make_grid() }
  , grid_shader_handle{ shader_manager->load_shader("grid").value() }
  , shader_handle{ shader }
{
    camera.pitch = degrees_to_radians(-30.f);
    camera.offset = {0.f, 0.6f, 0.f};
    camera.dolly = 3.f;

    glEnable(GL_DEPTH_TEST);
}

void
App::set_subject(OpenGLGeo geometry)
{
    subject.emplace(std::move(geometry));
}

void
App::step(platform const& platform)
{
    if (platform.mouse.right_button.is_down && platform.keyboard.alt.is_down) {
        camera.dolly += platform.time.seconds_since_last_frame * platform.mouse.delta_y;
    }

    if (platform.mouse.left_button.is_down && platform.keyboard.alt.is_down) {
        camera.orbit += platform.time.seconds_since_last_frame * platform.mouse.delta_x;
        camera.pitch += platform.time.seconds_since_last_frame * -platform.mouse.delta_y;
        camera.pitch = std::max(camera.pitch, -1.4f);
        camera.pitch = std::min(camera.pitch, 1.4f);
    }

#if 0
    if (platform.mouse.middle_button.is_down && platform.keyboard.alt.is_down) {
        camera.offset.x += platform.time.seconds_since_last_frame * -platform.mouse.delta_x;
        camera.offset.y += platform.time.seconds_since_last_frame * platform.mouse.delta_y;
    }
#endif

    camera.dolly += platform.time.seconds_since_last_frame * platform.mouse.wheel;

    if (platform.keyboard.r.pressed) {
        shader_manager->reload_shaders();
    }

    const auto width = static_cast<float>(platform.window.width);
    const auto height = static_cast<float>(platform.window.height);
    const auto perspective = mat4::perspective(degrees_to_radians(45.f), width / height, 0.01f, 1000.f);
    const auto projection = perspective * world_to_camera_matrix(&camera).forward_ref();
    //TODO: @redundant recalculates world to camera matrix.
    const auto camera_position = position(&camera);

    glViewport(0, 0, platform.window.width, platform.window.height);
    glClearColor(0.0f, 0.17f, 0.21f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto shader = shader_manager->get_shader(shader_handle);
    if (subject && shader) {
        shader->use_program(projection, camera_position, platform.time.seconds_since_starting);
        shader->set_model_matrix(
          mat4::rotate_around_y(platform.time.seconds_since_starting));
        subject.value().draw();
    }

    auto grid_shader = shader_manager->get_shader(grid_shader_handle);
    if (grid_shader) {
        grid_shader->use_program(projection, camera_position, platform.time.seconds_since_starting);
        grid.draw();
    }
}
