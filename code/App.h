#pragma once
#include <optional>

#include "Camera.h"
#include "OpenGLGeo.h"
#include "Shader.h"
#include "platform.h"

class App
{
  private:
    Camera camera;

    Shader shader;

    OpenGLGeo grid;
    Shader grid_shader;

    std::optional<OpenGLGeo> subject;

  public:
    explicit App(Shader shader);
    App(App&) = delete;
    App(App&&) = default;
    ~App() = default;

    void set_subject(OpenGLGeo geometry);
    void step(platform const& platform);
};
