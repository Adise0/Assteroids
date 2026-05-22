

#include "GameScene.h"
#include <cstdio>

namespace Assteroids {

using namespace Crow2D;
using namespace Crow2D::Components;


GameScene::GameScene() : Scene("Game Scene") {}

void GameScene::Load() { LoadHierachy(); }

void GameScene::LoadHierachy() { Camera &cam = rootGameObject->AddComponent<Camera>(); }
} // namespace Assteroids

