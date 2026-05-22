#pragma once

#include <Crow2D/Crow2D.h>


namespace Assteroids::Behaviours {

class MainMenuController : public Crow2D::Components::Behaviour {
  // #region Data
private:
  Crow2D::Components::UIRenderer *mainMenuRenderer = nullptr;
  // #endregion

  // #region Crow2D
private:
  void Awake() override;
  // #endregion

  // #region Listeners
private:
  static void OnPlay(const std::string &type, const std::string &payload);
  // #endregion
};
} // namespace Assteroids::Behaviours
