#pragma once

#include <Crow2D/Crow2D.h>

namespace Template {

class SampleScene : public Crow2D::Scenes::Scene {
  // #region Crow2D
public:
  SampleScene();
  void Load() override;
  // #endregion

  // #region Loads
private:
  void LoadUI();
  // #endregion
};
} // namespace Template
