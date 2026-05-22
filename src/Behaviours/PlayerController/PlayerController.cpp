

#include "PlayerController.h"
#include <Crow2D/GameObject.h>
#include <Crow2D/components/Animator.h>
#include <Crow2D/components/Renderer.h>
#include <Crow2D/dataObjects/AnimationClip.h>
#include <algorithm>
#include <stdexcept>

namespace Assteroids::Behaviours {
using namespace Crow2D;
using namespace Crow2D::Components;
using namespace Crow2D::Animations;
using namespace Crow2D::Scenes;
using namespace Crow2D::Inputs;
using namespace Crow2D::Types;

void PlayerController::Awake() { SetupVisuals(); }
void PlayerController::Update() {
  // #region Update
  MovePlayer();
  // #endregion
}


void PlayerController::SetupVisuals() {
  playerSprite = new Sprite("sprites/Player.png");
  engineSprite = new Sprite("sprites/Engine.png");
  engineEffects = new Sprite("sprites/EngineEffects.png");
  engineClip = new AnimationClip(
      engineEffects, Vector2(engineEffects->drawRect.w / 4.0f, engineEffects->drawRect.h));

  gameObject->AddComponent<Renderer>(engineSprite, Vector2(1, 1));
  gameObject->AddComponent<Renderer>(playerSprite, Vector2(1, 1));
  animator = &gameObject->AddComponent<Animator>(engineClip);
}

void PlayerController::MovePlayer() {
  // #region MovePlayer

  if (InputManager::GetKey("W").isPressed) {
    currentSpeed = std::clamp(currentSpeed + acceleration * Time::deltaTime, 0.0f, maxSpeed);
    // if (animator->isPaused) animator->Resume();
  } else if (currentSpeed > 0) {
    currentSpeed = std::clamp(currentSpeed - acceleration * Time::deltaTime, 0.0f, maxSpeed);
    // if (!animator->isPaused) animator->Pause();
  }

  transform->Translate(Vector3(transform->forward) * currentSpeed * Time::deltaTime);
  // #endregion
}


void PlayerController::OnDestroy() {
  delete playerSprite;
  delete engineSprite;
  delete engineEffects;
  delete engineClip;
}


} // namespace Assteroids::Behaviours
