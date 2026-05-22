#pragma once

#include <Crow2D/Crow2D.h>


namespace Assteroids::Behaviours {


class Asteroid : public Crow2D::Components::Behaviour {
  // #region Data
private:
  const int MinTurnSpeed = 40;
  const int MaxTurnSpeed = 180;

public:
  int type;
  Crow2D::Types::Vector2 dir;
  float speed;
  int turnSpeed;

  int currentHealth;
  // #endregion

  // #region Events
public:
  Crow2D::Events::Event<Asteroid *> OnAsteroidDestoryed;
  // #endregion


  // #region Crow2D
private:
  void Update() override;
  void OnTriggerEnter(const Crow2D::Components::Collider &other) override;
  // #endregion

  // #region Methods
public:
  void Init(const int &type, const Crow2D::Types::Vector2 &dir, const float &speed);

private:
  void Move();
  void SetupObject();

  // #endregion
};
} // namespace Assteroids::Behaviours
