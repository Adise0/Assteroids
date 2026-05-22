#include "MainMenu.h"
#include "MainMenuController.h"
#include <cstdio>

namespace Assteroids {

using namespace Crow2D;
using namespace Crow2D::Components;
using namespace Behaviours;


MainMenu::MainMenu() : Scene("Sample Scene") {}

void MainMenu::Load() { LoadUI(); }

void MainMenu::LoadUI() {

  GameObject &uiHolderGO = rootGameObject->CreateChild("UI Holder");
  Camera &cam = uiHolderGO.AddComponent<Camera>();
  UIRenderer &mainRenderer = uiHolderGO.AddComponent<UIRenderer>("ui/MainMenu/MainMenu.html");
  uiHolderGO.AddComponent<MainMenuController>();
}
} // namespace Assteroids

