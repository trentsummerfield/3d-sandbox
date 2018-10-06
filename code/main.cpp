#include <chrono>
#include <iostream>
#include <memory>

#include <GL/glew.h>

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "App.h"
#include "Loader.h"
#include "OpenGLGeo.h"
#include "Shader.h"
#include "platform.h"

using hr_clock = std::chrono::high_resolution_clock;
using float_seconds = std::chrono::duration<float>;

float
seconds_since(hr_clock::time_point time_point)
{
    auto duration_since_time_point = hr_clock::now() - time_point;
    return

      std::chrono::duration_cast<float_seconds>(duration_since_time_point)
        .count();
}

bool
handle_event(SDL_Event event, platform& platform)
{
    switch (event.type) {
        case SDL_QUIT:
            return false;
        case SDL_MOUSEMOTION: {
            platform.mouse.delta_x += event.motion.xrel;
            platform.mouse.delta_y += event.motion.yrel;
        } break;
        case SDL_MOUSEBUTTONDOWN: {
            switch (event.button.button) {
                case SDL_BUTTON_LEFT: {
                    press(platform.mouse.left_button);
                } break;
                case SDL_BUTTON_MIDDLE: {
                    press(platform.mouse.middle_button);
                } break;
                case SDL_BUTTON_RIGHT: {
                    press(platform.mouse.right_button);
                } break;
            }
        } break;
        case SDL_MOUSEBUTTONUP: {
            switch (event.button.button) {
                case SDL_BUTTON_LEFT: {
                    release(platform.mouse.left_button);
                } break;
                case SDL_BUTTON_MIDDLE: {
                    release(platform.mouse.middle_button);
                } break;
                case SDL_BUTTON_RIGHT: {
                    release(platform.mouse.right_button);
                } break;
            }
        } break;
        case SDL_KEYDOWN: {
            switch (event.key.keysym.sym) {
                case SDLK_LALT:
                case SDLK_RALT: {
                    press(platform.keyboard.alt);
                } break;
                case SDLK_ESCAPE:
                    return false;
            }
        } break;
        case SDL_KEYUP: {
            switch (event.key.keysym.sym) {
                case SDLK_LALT:
                case SDLK_RALT: {
                    release(platform.keyboard.alt);
                } break;
            }
        } break;
    }

    return true;
}

int
main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <obj filename> <shader name>"
                  << std::endl;
        return 1;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL Error: " << SDL_GetError();
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    auto window = SDL_CreateWindow("3D Sandbox",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   1920,
                                   1080,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    auto context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();

    auto shader = load_shader(argv[2]);
    if (!shader) {
        std::cout << "Failed to load shader" << std::endl;
        return 1;
    }
    auto filename = argv[1];
    auto geo = load_obj_file(filename);
    if (!geo) {
        std::cout << "Failed to load " << filename << std::endl;
    }

    if (shader && geo) {
        platform platform = {};
        auto app = App{ std::move(shader.value()) };
        app.set_subject(std::move(geo.value()));
        SDL_Event event;
        auto start_time = hr_clock::now();
        auto frame_start_time = hr_clock::now();
        bool running = true;
        while (running) {
            reset_platform(platform);
            SDL_GL_GetDrawableSize(
              window, &platform.window.width, &platform.window.height);

            while (SDL_PollEvent(&event) != 0) {
                running = handle_event(event, platform);
            }

            platform.time.seconds_since_starting = seconds_since(start_time);
            platform.time.seconds_since_last_frame =
              seconds_since(frame_start_time);
            frame_start_time = hr_clock::now();

            app.step(platform);
            SDL_GL_SwapWindow(window);
        }
    }

    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}
