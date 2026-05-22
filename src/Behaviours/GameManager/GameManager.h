#pragma once

#include <Crow2D/Crow2D.h>


namespace Assteroids::Behaviours {


class GameManager : public Crow2D::Components::Behaviour {
  // #region Data
public:
  Crow2D::GameObject *playerGO = nullptr;
  // #endregion

  // #region Crow2D
private:
  void Awake() override;
  // #endregion

  // #region Methods
private:
  // #endregion
};
} // namespace Assteroids::Behaviours
