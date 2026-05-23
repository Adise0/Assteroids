#pragma once

#include <Crow2D/Crow2D.h>


namespace Assteroids::Behaviours {


class Bullet : public Crow2D::Components::Behaviour {
  // #region Data
public:
  // TODO: base on stats i guess?
  float bulletspeed = 10.0f;
  float maxLifetime = 1.5f;
  float currentlifetime = 0;
  // #endregion

  // #region Crow2D
private:
  void Awake() override;
  void Update() override;
  // #endregion

  // #region Methods
private:
  void SetupObject();
  void Move();
  // #endregion
};

} // namespace Assteroids::Behaviours
