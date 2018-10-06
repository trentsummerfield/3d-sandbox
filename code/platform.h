#pragma once

struct button
{
    bool is_down;
    bool pressed;
    bool released;
};

struct platform
{
    struct
    {
        int width;
        int height;
    } window;
    struct
    {
        float delta_x;
        float delta_y;
        button left_button;
        button middle_button;
        button right_button;
    } mouse;
    struct
    {
        button alt;
    } keyboard;
    struct
    {
        float seconds_since_starting;
        float seconds_since_last_frame;
    } time;
};

inline void
reset_button(button& button)
{
    button.pressed = false;
    button.released = false;
}

inline void
reset_platform(platform& platform)
{
    platform.mouse.delta_x = 0;
    platform.mouse.delta_y = 0;
    reset_button(platform.mouse.left_button);
    reset_button(platform.mouse.middle_button);
    reset_button(platform.mouse.right_button);

    reset_button(platform.keyboard.alt);
}

inline void
press(button& button)
{
    if (!button.is_down) {
        button.pressed = true;
    }
    button.is_down = true;
}

inline void
release(button& button)
{
    if (button.is_down) {
        button.released = true;
    }
    button.is_down = false;
}