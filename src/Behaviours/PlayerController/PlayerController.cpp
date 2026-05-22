

#include "PlayerController.h"
#include <Crow2D/GameObject.h>
#include <Crow2D/components/Animator.h>
#include <Crow2D/components/Renderer.h>
#include <Crow2D/dataObjects/AnimationClip.h>
#include <Crow2D/dataObjects/Vectors.h>
#include <algorithm>
#include <stdexcept>
#include <string>

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
  LoadLevelSprites(1);
  Vector2 size(1, 1);
  engineRenderer = &gameObject->AddComponent<Renderer>(engineSprite, size);
  shipRenderer = &gameObject->AddComponent<Renderer>(shipSprites[maxLives - 1], size);
  GameObject &animatorGO = gameObject->CreateChild("Animations");
  animatorGO.transform->position -= Vector3(0, 0, 1);
  animatorGO.AddComponent<Renderer>(idleSprite, size);
  animator = &animatorGO.AddComponent<Animator>(idleClip);
}

void PlayerController::LoadLevelSprites(short level) {
  CleanSprites();


  for (short i = 0; i < maxLives; i++) {
    std::string name =
        "sprites/ship/lvl" + std::to_string(level) + "/Ship_" + std::to_string(i) + ".png";

    shipSprites.push_back(new Sprite(name.c_str()));
  }

  engineSprite = new Sprite(("sprites/ship/lvl" + std::to_string(level) + "/Engine.png").c_str());
  idleSprite = new Sprite(("sprites/ship/lvl" + std::to_string(level) + "/Idle.png").c_str());
  powerSprite = new Sprite(("sprites/ship/lvl" + std::to_string(level) + "/Power.png").c_str());

  Vector2 idleCellSize(idleSprite->drawRect.w / 3.0f, idleSprite->drawRect.h);
  idleClip = new AnimationClip(idleSprite, idleCellSize);

  Vector2 powerCellSize(powerSprite->drawRect.w / 4.0f, powerSprite->drawRect.h);
  powerClip = new AnimationClip(powerSprite, powerCellSize);
}

void PlayerController::MovePlayer() {
  // #region MovePlayer

  if (InputManager::GetKey("W").isPressed) {
    currentSpeed = std::clamp(currentSpeed + acceleration * Time::deltaTime, 0.0f, maxSpeed);
    if (animator->currentClip != powerClip) animator->Play(powerClip);
  } else if (currentSpeed > 0) {
    currentSpeed = std::clamp(currentSpeed - acceleration * Time::deltaTime, 0.0f, maxSpeed);
    if (animator->currentClip != idleClip) animator->Play(idleClip);
  }

  transform->Translate(Vector3(transform->forward) * currentSpeed * Time::deltaTime);
  // #endregion
}


void PlayerController::CleanSprites() {
  if (!shipSprites.empty()) {
    for (Sprite *shipSprite : shipSprites) {
      delete shipSprite;
    }
  }
  shipSprites.clear();
  if (engineSprite) delete engineSprite;
  if (idleSprite) delete idleSprite;
  if (powerSprite) delete powerSprite;

  if (idleClip) delete idleClip;
  if (powerClip) delete powerClip;
}

void PlayerController::OnDestroy() { CleanSprites(); }


} // namespace Assteroids::Behaviours
