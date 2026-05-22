#include <Crow2D/dataObjects/Vectors.h>
#include <cstdio>
#define NOMINMAX

#include "Bullet.h"
#include "PlayerController.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>


namespace Assteroids::Behaviours {
using namespace Crow2D;
using namespace Crow2D::Components;
using namespace Crow2D::Animations;
using namespace Crow2D::Scenes;
using namespace Crow2D::Inputs;
using namespace Crow2D::Types;
using namespace Data;

void PlayerController::Awake() {
  stats = Stats::Singleton;
  fireTimer = 1.0f / stats->fireRate;
  SetupVisuals();
}
void PlayerController::Update() {
  // #region Update
  MovePlayer();
  RotatePlayer();
  Shoot();
  // #endregion
}

void PlayerController::Shoot() {
  if (currentFireTimer < fireTimer) {
    currentFireTimer += Time::deltaTime;
    return;
  }
  if (currentFireTimer != fireTimer) currentFireTimer = fireTimer;

  if (InputManager::GetKey("Space").isPressed) {
    currentFireTimer = 0;
    printf("Shooting!\n");

    GameObject &bulletGO = gameObject->scene->rootGameObject->CreateChild("Bullet");
    bulletGO.transform->position =
        transform->position + (Vector3(transform->forward) * Vector2(0.3f, 0.3f));

    bulletGO.transform->rotation = transform->rotation;
    bulletGO.AddComponent<Bullet>();
  }
}


void PlayerController::SetupVisuals() {
  LoadLevelSprites(1);
  Vector2 size(1, 1);
  engineRenderer = &gameObject->AddComponent<Renderer>(engineSprite, size);
  shipRenderer = &gameObject->AddComponent<Renderer>(shipSprites[MaxLives], size);
  GameObject &animatorGO = gameObject->CreateChild("Animations");
  animatorGO.transform->position -= Vector3(0, 0, 1);
  animatorGO.AddComponent<Renderer>(idleSprite, size);
  animator = &animatorGO.AddComponent<Animator>(idleClip);
}

void PlayerController::LoadLevelSprites(short level) {
  CleanSprites();


  for (short i = 0; i <= MaxLives; i++) {
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
    velocity += Vector3(transform->forward) * stats->acceleration * Time::deltaTime;

    if (velocity.SqrMagnitude() > std::pow(stats->maxSpeed, 2)) {
      velocity = velocity.Normalized() * stats->maxSpeed;
    }

    if (animator->currentClip != powerClip) animator->Play(powerClip);
  } else {
    if (animator->currentClip != idleClip) animator->Play(idleClip);
    float speed = velocity.Magnitude();
    if (speed > 0.f) {
      float newSpeed = speed - stats->deceleration * Time::deltaTime;
      if (newSpeed <= 0.f) {
        velocity = Vector2::Zero;
      } else {
        velocity = velocity.Normalized() * newSpeed;
      }
    }
  }


  transform->Translate(Vector3(velocity) * Time::deltaTime);
  // #endregion
}

void PlayerController::RotatePlayer() {
  // #region MovePlayer
  float angle = transform->rotation;
  if (InputManager::GetKey("A").isPressed) {
    angle += -1 * stats->turnSpeed * Time::deltaTime;
  }
  if (InputManager::GetKey("D").isPressed) {
    angle += (float)stats->turnSpeed * Time::deltaTime;
  }

  transform->rotation = angle;
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
