#pragma once

#include "mat4_invertable.h"
#include "vec3.h"

class Camera
{
  private:
    vec3 offset;
    float pitch;
    float orbit;
    float dolly;

  public:
    Camera();
    Camera(Camera const&) = default;
    Camera(Camera&&) = default;
    ~Camera() = default;

    void dolly_by(float delta) { dolly += delta; }
    void orbit_by(float delta) { orbit += delta; }
    void pitch_by(float delta)
    {
        pitch += delta;
        pitch = std::max(pitch, -1.4f);
        pitch = std::min(pitch, 1.4f);
    }
    void offset_x_by(float delta) { offset.x += delta; }
    void offset_y_by(float delta) { offset.y += delta; }

    mat4_invertable world_to_camera_matrix() const;
    vec3 position() const;
};
