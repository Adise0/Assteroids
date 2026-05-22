#pragma once

#include <Crow2D/Crow2D.h>

namespace Template {

class MainMenu : public Crow2D::Scenes::Scene {
  // #region Crow2D
public:
  MainMenu();
  void Load() override;
  // #endregion

  // #region Loads
private:
  void LoadUI();
  // #endregion
};
} // namespace Template
