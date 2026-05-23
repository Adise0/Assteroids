#pragma once

#include "Stats.h"
#include <Crow2D/Crow2D.h>
#include <Crow2D/dataObjects/Vectors.h>
#include <vector>

namespace Assteroids::Behaviours {

class Asteroid;

class GameManager : public Crow2D::Components::Behaviour {
  // #region Getters
  int GetPoints() const;
  // #endregion

  // #region Data
public:
  Crow2D::GameObject *playerGO = nullptr;

public:
  GETTER_PROPERTY(GameManager, int, points, GetPoints);

private:
  Crow2D::Components::UIRenderer *hud = nullptr;

private:
  const float MinWait = 0.5f;
  const float InitialWait = 4.0f;
  const float ScaleFactor = 0.005f;
  const float MinAsteroidSpeed = 0.3f;
  const float MaxAsteroidSpeed = 1.2f;
  const short MaxAsteroids = 10;

  int _points;
  short asteroids = 0;
  float spawnWait = InitialWait;
  float currentWaitTime = spawnWait;
  // #endregion

  // #region Crow2D
private:
  void Awake() override;
  void Start() override;
  void Update() override;
  // #endregion

  // #region Methods
private:
  void SpawnAsteroids();
  void SpawnAsteroid(const Crow2D::Types::Vector3 &spawnPos, const int &type,
                     const Crow2D::Types::Vector2 &dir, const float &speed);
  void OnAsteroidDestroyed(const Asteroid *asteroid);


  void OpenShop();
  void PickUpgrade(Data::Stat stat);
  // #endregion
};
} // namespace Assteroids::Behaviours
