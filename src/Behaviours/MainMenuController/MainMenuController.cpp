
#include "MainMenuController.h"
#include "GameScene.h"
#include <Crow2D/SceneManager.h>
#include <stdexcept>

namespace Assteroids::Behaviours {
using namespace Crow2D::Components;
using namespace Crow2D::Scenes;

void MainMenuController::Awake() {
  // #region Awake
  mainMenuRenderer = gameObject->GetComponent<UIRenderer>();
  if (!mainMenuRenderer) throw std::runtime_error("UIManager requires a UIRenderer component");

  mainMenuRenderer->bridge->On("Play", OnPlay);
  // #endregion
}

void MainMenuController::OnPlay(const std::string &type, const std::string &payload) {
  // #region OnPlay
  GameScene *gameScene = new GameScene();
  SceneManager::SetSceneAsActive(*gameScene);
  // #endregion
}

} // namespace Assteroids::Behaviours
