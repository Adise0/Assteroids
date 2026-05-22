#pragma once


#include <Crow2D/Crow2D.h>


namespace Assteroids::Behaviours {


class Teleporter : public Crow2D::Components::Behaviour {


  // #region Crow2D
private:
  void Update() override;
  // #endregion

  // #region Methods
private:
  void CheckBounds();
  // #endregion
};

} // namespace Assteroids::Behaviours
