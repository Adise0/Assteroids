
#include "GameManager.h"
#include "Asteroid.h"
#include <Crow2D/components/UIRenderer.h>
#include <stdexcept>
#include <string>

namespace Assteroids::Behaviours {
using namespace Crow2D;
using namespace Crow2D::Components;
using namespace Crow2D::Scenes;
using namespace Crow2D::Types;
using namespace Data;


int GameManager::GetPoints() const { return _points; }

void GameManager::Awake() {
  // #region Awake
  hud = gameObject->GetComponent<UIRenderer>();
  hud->bridge->On("PickUpgrade", [this](const std::string &type, const std::string &payload) {
    PickUpgrade(Stats::GetStatByName(payload));
  });
  // #endregion
}

void GameManager::Update() {
  if (!Camera::activeCamera) return;
  SpawnAsteroids();
}

void GameManager::SpawnAsteroids() {
  if (asteroids >= MaxAsteroids) return;
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

  SpawnAsteroid(Vector3(spawnPos), type, dir, speed);
}

void GameManager::SpawnAsteroid(const Crow2D::Types::Vector3 &spawnPos, const int &type,
                                const Crow2D::Types::Vector2 &dir, const float &speed) {
  GameObject &asteroidGO = gameObject->scene->rootGameObject->CreateChild("Asteroid");
  asteroidGO.transform->position = spawnPos;
  Asteroid &asteroid = asteroidGO.AddComponent<Asteroid>();
  asteroid.Init(type, dir, speed);
  asteroid.OnAsteroidDestoryed += [this](Asteroid *asteroid) { OnAsteroidDestroyed(asteroid); };
  asteroids++;
}

void GameManager::OnAsteroidDestroyed(const Asteroid *asteroid) {
  int pointsToAdd = (asteroid->type + 1) * 10;
  _points += pointsToAdd;
  hud->bridge->Send("Points", std::to_string(_points));
  asteroids--;

  if (asteroid->type == 0) return;

  Vector2 newDir1 = Vector2((std::rand() / (float)RAND_MAX), (std::rand() / (float)RAND_MAX));
  Vector2 newDir2 = Vector2((std::rand() / (float)RAND_MAX), (std::rand() / (float)RAND_MAX));

  float newSpeed = asteroid->speed * 1.3f;
  int newType = asteroid->type - 1;

  SpawnAsteroid(asteroid->transform->position, newType, newDir1, newSpeed);
  SpawnAsteroid(asteroid->transform->position, newType, newDir2, newSpeed);
}



void GameManager::OpenShop(const std::vector<Data::Stat> &stats) {

  std::string payload = "[";
  for (Stat stat : stats) {
    payload += "\"" + Stats::GetStatName(stat) + ",\"";
  }
  payload += "]";

  hud->bridge->Send("OpenShop", payload);
}

void GameManager::PickUpgrade(Stat stat) {
  Stats::Singleton->Upgrade(stat);

  std::string payload = "{";
  payload += "\"name\":\"" + Stats::GetStatName(stat) + "\",";
  payload += "\"lvl\":" + std::to_string(Stats::GetStatLevel(stat)) + ",";
  payload += "\"value\":" + std::to_string(Stats::GetStat(stat)) + "";

  payload += "}";

  hud->bridge->Send("UpdateStat", payload);
}

} // namespace Assteroids::Behaviours
