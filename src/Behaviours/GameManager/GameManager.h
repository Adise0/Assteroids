#pragma once

#include <Crow2D/Crow2D.h>
#include <Crow2D/dataObjects/Vectors.h>
#include <Crow2D/properties/GetterProperty.h>


namespace Assteroids::Behaviours {


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
  const float MinWait = 0.5f;
  const float InitialWait = 4.0f;
  const float ScaleFactor = 0.005f;
  const float MinAsteroidSpeed = 0.3f;
  const float MaxAsteroidSpeed = 1.2f;

  int _points;
  float spawnWait = InitialWait;
  float currentWaitTime = spawnWait;
  // #endregion

  // #region Crow2D
private:
  void Awake() override;
  void Update() override;
  // #endregion

  // #region Methods
private:
  void SpawnAsteroids();
  // #endregion
};
} // namespace Assteroids::Behaviours
