#pragma once
#include <optional>

#include "OpenGLGeo.h"

std::optional<OpenGLGeo>
load_obj_file(std::string const& filename);
