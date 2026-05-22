

#include "GameScene.h"
#include "GameManager.h"
#include "PlayerController.h"
#include <Crow2D/GameObject.h>
#include <Crow2D/components/Renderer.h>
#include <Crow2D/dataObjects/Sprite.h>
#include <Crow2D/dataObjects/Vectors.h>
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

  GameObject &playerGO = rootGameObject->CreateChild("Player");
  playerGO.AddComponent<PlayerController>();
  gameManager.playerGO = &playerGO;
}
} // namespace Assteroids

