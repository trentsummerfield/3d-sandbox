#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include "Shader.h"

class ShaderHandle
{
  private:
    uint32_t handle;
    ShaderHandle(uint32_t handle)
      : handle(handle)
    {}

  public:
    friend class ShaderManager;
    friend struct ShaderHandleHash;

    ShaderHandle(ShaderHandle const&) = default;
    ShaderHandle(ShaderHandle&&) = default;
    ~ShaderHandle() = default;

    bool operator==(ShaderHandle const& other) const
    {
        return handle == other.handle;
    }
};

struct ShaderHandleHash
{
    size_t operator()(ShaderHandle const& handle) const noexcept
    {
        return std::hash<uint32_t>{}(handle.handle);
    }
};

using ShaderValue = std::pair<std::string, std::shared_ptr<Shader>>;
using ShaderMap =
  std::unordered_map<ShaderHandle, ShaderValue, ShaderHandleHash>;

class ShaderManager
{
  private:
    uint32_t next_handle{ 1 };
    ShaderMap shaders;

  public:
    ShaderManager() = default;
    ShaderManager(ShaderManager const&) = delete;
    ShaderManager(ShaderManager&&) = delete;
    ~ShaderManager() = default;

    std::optional<ShaderHandle> load_shader(std::string const& shader_name);
    std::shared_ptr<Shader> get_shader(ShaderHandle handle);
    void reload_shaders();
};
