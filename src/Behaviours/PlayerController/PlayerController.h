#pragma once

#include "Stats.h"
#include <Crow2D/Crow2D.h>
#include <vector>


namespace Assteroids::Behaviours {


class PlayerController : public Crow2D::Components::Behaviour {
  // #region Getters
  short GetCurrentLives() const;
  // #endregion
  // #region Data
public:
  GETTER_PROPERTY(PlayerController, short, currentLives, GetCurrentLives);
  const short MaxLives = 3;

private:
  short _currentLives = MaxLives;
  float currentFireTimer = 100;
  float fireTimer = 0;

  const float GracePeriod = 3;
  float currentGraceTimer;

private:
  Data::Stats *stats;
  Crow2D::Types::Vector2 velocity;
  Crow2D::Components::Animator *animator;
  Crow2D::Components::Renderer *shipRenderer;
  Crow2D::Components::Renderer *engineRenderer;

private:
  std::vector<Crow2D::Types::Sprite *> shipSprites;
  Crow2D::Types::Sprite *engineSprite = nullptr;
  Crow2D::Types::Sprite *idleSprite = nullptr;
  Crow2D::Types::Sprite *powerSprite = nullptr;

  Crow2D::Animations::AnimationClip *idleClip = nullptr;
  Crow2D::Animations::AnimationClip *powerClip = nullptr;
  // #endregion

  // #region Crow2D
private:
  void Awake() override;
  void Update() override;
  void OnDestroy() override;
  // #endregion

  // #region Methods
public:
  void TakeDamage();

private:
  void SetupVisuals();
  void LoadLevelSprites(short level);

  void MovePlayer();
  void RotatePlayer();
  void Shoot();

  void CleanSprites();
  // #endregion
};
} // namespace Assteroids::Behaviours
