#define NOMINMAX

#include "GameManager.h"
#include "Asteroid.h"
#include <cstdio>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace Assteroids::Behaviours {
using namespace Crow2D;
using namespace Crow2D::Components;
using namespace Crow2D::Scenes;
using namespace Crow2D::Types;
using namespace Data;
using namespace nlohmann;


int GameManager::GetPoints() const { return _points; }

void GameManager::Awake() {
  // #region Awake
  hud = gameObject->GetComponent<UIRenderer>();
  hud->bridge->On("PickUpgrade", [this](const std::string &type, const std::string &payload) {
    PickUpgrade(Stats::GetStatByName(payload));
  });


  // #endregion
}

void GameManager::Start() {
  json payload;
  for (short i = 0; i < (short)Stat::Count; i++) {

    payload += {
        {"name", Stats::GetStatName((Stat)i)},
        {"value", Stats::GetStat((Stat)i)},
    };
  }
  hud->bridge->On("__loaded", [this, payload](const std::string, const std::string) {
    hud->bridge->Send("Stats", payload.dump());
  });
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

  int old = _points;
  _points += pointsToAdd;
  hud->bridge->Send("Points", std::to_string(_points));

  bool openShop = (old / 100) != (_points / 100);

  if (openShop) OpenShop();


  asteroids--;

  if (asteroid->type == 0) return;

  Vector2 newDir1 = Vector2((std::rand() / (float)RAND_MAX), (std::rand() / (float)RAND_MAX));
  Vector2 newDir2 = Vector2((std::rand() / (float)RAND_MAX), (std::rand() / (float)RAND_MAX));

  float newSpeed = asteroid->speed * 1.3f;
  int newType = asteroid->type - 1;

  SpawnAsteroid(asteroid->transform->position, newType, newDir1, newSpeed);
  SpawnAsteroid(asteroid->transform->position, newType, newDir2, newSpeed);
}



void GameManager::OpenShop() {
  std::vector<Stat> stats;
  std::vector<Stat> allStats;

  for (short i = 0; i < (short)Stat::Count; i++) {
    short statLevel = Stats::GetStatLevel((Stat)i);
    if (statLevel == Stats::MaxLevel) continue;
    allStats.push_back((Stat)i);
  }

  short amount = std::min((int)allStats.size(), 3);

  if (amount == 0) return;

  Time::timeScale = 0;

  while (stats.size() != amount) {
    int statIndex = rand() % allStats.size();
    stats.push_back(allStats[statIndex]);
    allStats.erase(allStats.begin() + statIndex);
  }


  json payload;
  for (Stat stat : stats) {
    short statLevel = Stats::GetStatLevel(stat);

    payload += {{"name", Stats::GetStatName(stat)},
                {"level", statLevel + 1},
                {"currentValue", Stats::GetStat(stat)},
                {"newValue", Stats::GetStatAtLevel(stat, statLevel + 1)}};
  }


  hud->bridge->Send("OpenShop", payload.dump());
}

void GameManager::PickUpgrade(Stat stat) {
  Stats::Singleton->Upgrade(stat);

  json payload = {{"name", Stats::GetStatName(stat)},
                  {"level", Stats::GetStatLevel(stat)},
                  {"value", Stats::GetStat(stat)}};



  hud->bridge->Send("UpdateStat", payload.dump());
  Time::timeScale = 1;
}

} // namespace Assteroids::Behaviours
