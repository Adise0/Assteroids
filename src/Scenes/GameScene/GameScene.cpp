

#include "GameScene.h"
#include "GameManager.h"
#include "PlayerController.h"
#include "Teleporter.h"
#include <Crow2D/components/UIRenderer.h>
#include <cstdio>

namespace Assteroids {

using namespace Crow2D;
using namespace Crow2D::Components;
using namespace Behaviours;


GameScene::GameScene() : Scene("Game Scene") {}

void GameScene::Load() { LoadHierachy(); }

void GameScene::LoadHierachy() {
  Camera &cam = rootGameObject->AddComponent<Camera>();
  GameManager &gameManager = rootGameObject->AddComponent<GameManager>();
  rootGameObject->AddComponent<UIRenderer>("ui/HUD/HUD.html");

  GameObject &playerGO = rootGameObject->CreateChild("Player");
  playerGO.AddComponent<PlayerController>();
  playerGO.AddComponent<Teleporter>();
  gameManager.playerGO = &playerGO;
}
} // namespace Assteroids

