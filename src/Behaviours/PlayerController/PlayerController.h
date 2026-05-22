#pragma once

#include <Crow2D/Crow2D.h>
#include <Crow2D/components/Animator.h>
#include <Crow2D/dataObjects/AnimationClip.h>
#include <Crow2D/dataObjects/Sprite.h>


namespace Assteroids::Behaviours {


class PlayerController : public Crow2D::Components::Behaviour {
  // #region Data
public:
  float acceleration = 2;
  float maxSpeed = 3;
  float turnSpeed = 45;

private:
  float currentSpeed = 0;

  Crow2D::Components::Animator *animator;

private:
  Crow2D::Types::Sprite *playerSprite = nullptr;
  Crow2D::Types::Sprite *engineSprite = nullptr;
  Crow2D::Types::Sprite *engineEffects = nullptr;
  Crow2D::Animations::AnimationClip *engineClip = nullptr;
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
  void MovePlayer();
  void RotatePlayer();
  void Shoot();
  // #endregion
};
} // namespace Assteroids::Behaviours
