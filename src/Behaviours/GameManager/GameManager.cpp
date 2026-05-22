
#include "GameManager.h"
#include "Asteroid.h"
#include <Crow2D/components/Camera.h>
#include <stdexcept>

namespace Assteroids::Behaviours {
using namespace Crow2D;
using namespace Crow2D::Components;
using namespace Crow2D::Scenes;
using namespace Crow2D::Types;


int GameManager::GetPoints() const { return _points; }

void GameManager::Awake() {
  // #region Awake

  // #endregion
}

void GameManager::Update() {
  if (!Camera::activeCamera) return;
  SpawnAsteroids();
}

void GameManager::SpawnAsteroids() {
  if (currentWaitTime < spawnWait) {
    currentWaitTime += Time::deltaTime;
    return;
  }

  spawnWait = InitialWait / (1.0f + (float)points * ScaleFactor);
  currentWaitTime = 0;


  // 0->top | 1->bottom | 2->left | 3->right
  int edge = std::rand() % 4;
  Camera *cam = Camera::activeCamera;

  Vector2 spawnPos;
  Vector2 target;
  float width = cam->rect.get().Right() - cam->rect.get().Left();
  float height = cam->rect.get().Top() - cam->rect.get().Bottom();

  switch (edge) {
  case 0:
    { // top → bottom
      float spawnX = cam->rect.get().Left() + (std::rand() / (float)RAND_MAX) * width;
      float targetX = cam->rect.get().Left() + (std::rand() / (float)RAND_MAX) * width;
      spawnPos = Vector2(spawnX, cam->rect.get().Top() + 2);
      target = Vector2(targetX, cam->rect.get().Bottom() - 2);
      break;
    }
  case 1:
    { // bottom → top
      float spawnX = cam->rect.get().Left() + (std::rand() / (float)RAND_MAX) * width;
      float targetX = cam->rect.get().Left() + (std::rand() / (float)RAND_MAX) * width;
      spawnPos = Vector2(spawnX, cam->rect.get().Bottom() - 2);
      target = Vector2(targetX, cam->rect.get().Top() + 2);
      break;
    }
  case 2:
    { // left → right
      float spawnY = cam->rect.get().Bottom() + (std::rand() / (float)RAND_MAX) * height;
      float targetY = cam->rect.get().Bottom() + (std::rand() / (float)RAND_MAX) * height;
      spawnPos = Vector2(cam->rect.get().Left() - 2, spawnY);
      target = Vector2(cam->rect.get().Right() + 2, targetY);
      break;
    }
  case 3:
    { // right → left
      float spawnY = cam->rect.get().Bottom() + (std::rand() / (float)RAND_MAX) * height;
      float targetY = cam->rect.get().Bottom() + (std::rand() / (float)RAND_MAX) * height;
      spawnPos = Vector2(cam->rect.get().Right() + 2, spawnY);
      target = Vector2(cam->rect.get().Left() - 2, targetY);
      break;
    }
  }

  int type = std::rand() % 3;
  Vector2 dir = (target - spawnPos).Normalized();
  float speed =
      MinAsteroidSpeed + (std::rand() / (float)RAND_MAX) * (MaxAsteroidSpeed - MinAsteroidSpeed);

  GameObject &asteroidGO = gameObject->scene->rootGameObject->CreateChild("Asteroid");
  asteroidGO.transform->position = Vector3(spawnPos);
  asteroidGO.AddComponent<Asteroid>().Init(type, dir, speed);
  // Spawn
}



} // namespace Assteroids::Behaviours
