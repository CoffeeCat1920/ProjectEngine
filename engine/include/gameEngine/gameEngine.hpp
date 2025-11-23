#pragma once
#include <ComponentRegistry/Component.hpp>
#include <ECS/ECS.h>
#include <ECS/component/component.hpp>
#include <ECS/entity/entity.hpp>
#include <ECS/system/system.hpp>
#include <Scene/Scene.hpp>
#include <SystemRegistry/System.hpp>
#include <SystemRegistry/SystemRegistry.hpp>
#include <cameraController/cameraController.hpp>
#include <core/colors.hpp>
#include <core/setting.hpp>
#include <filesystem>
#include <raylib.h>
#include <string>

struct WindowConfig {
  int blockSize = 32;
  int width = 10;
  int height = 6;
  int scale = DEFAULT_SCALE;

  WindowConfig() = default;
  WindowConfig(int block, int w, int h, int s = DEFAULT_SCALE)
      : blockSize(block), width(w), height(h), scale(s) {}

  int rendering_width() const { return width * blockSize * scale; }
  int rendering_height() const { return height * blockSize * scale; }
};

class GameEngine {
private:
  ECS &gEcs = ECS::Instance();
  WindowConfig windowConfig;
  SystemRegistry &systemRegistery = SystemRegistry::Instance();
  std::string title;
  Color backgroundColor;
  CameraController cameraController;

  explicit GameEngine(const WindowConfig &config, const std::string &title,
                      Color background = BLACK)
      : windowConfig(config), title(title), backgroundColor(background),
        cameraController(windowConfig.scale) {}

  void BeginFrame() {
    BeginDrawing();
    ClearBackground(backgroundColor);
  }

  void EndFrame() {
    int fps = GetFPS();
    std::string fpsText = "FPS: " + std::to_string(fps);
    int textWidth = MeasureText(fpsText.c_str(), 20);

    DrawText(fpsText.c_str(), windowConfig.rendering_width() - textWidth - 10,
             10, 20, GRUVBOX_AQUA);

    EndDrawing();
  }

public:
  GameEngine(const GameEngine &) = delete;
  GameEngine &operator=(const GameEngine &) = delete;
  GameEngine(GameEngine &&) = delete;
  GameEngine &operator=(GameEngine &&) = delete;

  static GameEngine &Instance(const WindowConfig &config = {},
                              const std::string &title = "Window",
                              Color background = BACKGROUND) {
    static GameEngine instance(config, title, background);
    return instance;
  }

  void Init() {
    InitWindow(windowConfig.rendering_width(), windowConfig.rendering_height(),
               title.c_str());
    SetTargetFPS(60);
  }

  template <typename... Components>
  Entity CreateEntity(const std::string &name, Components &&...comps) {
    Entity e = gEcs.AddEntity(name);
    gEcs.AddComponent(e, std::forward<Components>(comps)...);
    return e;
  }

  void LoadScene(std::filesystem::path scenePath) { Scene scene(scenePath); }

  void Run() {
    while (!WindowShouldClose()) {
      BeginFrame();
      systemRegistery.RenderUpdate();
      EndFrame();
      systemRegistery.PhysicsUpdate();
    }
  }

  ~GameEngine() { CloseWindow(); }

  const WindowConfig &GetConfig() const { return windowConfig; }
};
