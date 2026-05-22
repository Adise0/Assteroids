#pragma once

#include <Crow2D/Component.h>
#include <Crow2D/Crow2D.h>
#include <Crow2D/components/Animator.h>
#include <Crow2D/components/Renderer.h>
#include <Crow2D/dataObjects/AnimationClip.h>
#include <Crow2D/dataObjects/Sprite.h>
#include <vector>


namespace Assteroids::Behaviours {


class PlayerController : public Crow2D::Components::Behaviour {
  // #region Data
public:
  float acceleration = 2;
  float deacceleration = 1;
  float maxSpeed = 10;
  float turnSpeed = 180;
  short maxLives = 4;
  short currentLives = maxLives;

private:
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
