#pragma once

#include <Crow2D/Crow2D.h>


namespace Assteroids::Behaviours {


class Asteroid : public Crow2D::Components::Behaviour {
  // #region Data
private:
  const int MinTurnSpeed = 40;
  const int MaxTurnSpeed = 180;

  int type;
  Crow2D::Types::Vector2 dir;
  float speed;
  int turnSpeed;
  // #endregion


  // #region Crow2D
private:
  void Update() override;
  // #endregion

  // #region Methods
public:
  void Init(const int &type, const Crow2D::Types::Vector2 &dir, const float &speed);

private:
  void Move();
  void SetupVisuals();
  // #endregion
};
} // namespace Assteroids::Behaviours
