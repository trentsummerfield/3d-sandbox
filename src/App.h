#pragma once
#include <memory>
#include <optional>

#include "camera.h"
#include "OpenGLGeo.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "platform.h"

class App
{
  private:
    struct camera camera;

    std::shared_ptr<ShaderManager> shader_manager;

    OpenGLGeo grid;
    ShaderHandle grid_shader_handle;

    ShaderHandle shader_handle;
    std::optional<OpenGLGeo> subject;

  public:
    App(std::shared_ptr<ShaderManager> shader_manager, ShaderHandle shader);
    App(App&) = delete;
    App(App&&) = default;
    ~App() = default;

    void set_subject(OpenGLGeo geometry);
    void step(platform const& platform);
};
