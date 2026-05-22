#pragma once

#include <Crow2D/Crow2D.h>

namespace Assteroids {

class GameScene : public Crow2D::Scenes::Scene {
  // #region Crow2D
public:
  GameScene();
  void Load() override;
  // #endregion

  // #region Loads
private:
  void LoadHierachy();
  // #endregion
};
} // namespace Assteroids
