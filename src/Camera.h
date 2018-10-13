#pragma once

#include "mat4_invertable.h"
#include "vec3.h"

class Camera
{
  private:
    vec3 offset{ 0.0, 0.0, 1.0 };
    float pitch{ 0.0 };
    float orbit{ 0.0 };
    float dolly{ 0.0 };

  public:
    Camera() = default;
    Camera(Camera const&) = default;
    Camera(Camera&&) = default;
    ~Camera() = default;

    void set_offset(vec3 offset) { this->offset = offset; }
    void set_pitch(float pitch) { this->pitch = pitch; }
    void set_orbit(float orbit) { this->orbit = orbit; }
    void set_dolly(float dolly) { this->dolly = dolly; }

    void pitch_by(float delta)
    {
        pitch += delta;
        pitch = std::max(pitch, -1.4f);
        pitch = std::min(pitch, 1.4f);
    }
    void orbit_by(float delta) { orbit += delta; }
    void dolly_by(float delta) { dolly += delta; }
    void offset_by(vec3 delta) { offset += delta; }
    void offset_x_by(float delta) { offset.x += delta; }
    void offset_y_by(float delta) { offset.y += delta; }

    mat4_invertable world_to_camera_matrix() const;
    vec3 position() const;
};
