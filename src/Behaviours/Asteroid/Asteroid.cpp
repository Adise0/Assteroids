#include "Asteroid.h"
#include <Crow2D/TimeManager.h>
#include <Crow2D/dataObjects/Sprite.h>
#include <Crow2D/dataObjects/Vectors.h>

namespace Assteroids::Behaviours {
using namespace Crow2D;
using namespace Crow2D::Components;
using namespace Crow2D::Types;

void Asteroid::Init(const int &type, const Crow2D::Types::Vector2 &dir, const float &speed) {

  this->type = type;
  this->dir = dir;
  this->speed = speed;
  turnSpeed = MinTurnSpeed + std::rand() % (MaxTurnSpeed - MinTurnSpeed);

  currentHealth = (type + 1) * 2;

  SetupVisuals();
}


void Asteroid::Update() { Move(); }

void Asteroid::OnTriggerEnter(const Crow2D::Components::Collider &other) {
  if (other.gameObject->name != "Bullet") return;
  Destroy(other.gameObject);
  currentHealth--;
  if (currentHealth > 0) return;
  OnAsteroidDestoryed(this);
  Destroy(gameObject);
}

void Asteroid::SetupVisuals() {

  Vector2 size;
  switch (type) {
  case 0:
    size = Vector2(0.5f, 0.5f);
    break;
  case 1:
    size = Vector2(1.0f, 1.0f);
    break;
  case 2:
    size = Vector2(1.5f, 1.5f);
    break;
  }
  gameObject->AddComponent<Renderer>(Primitives::Circle, size);
}
void Asteroid::Move() {

  transform->Rotate(turnSpeed * Time::deltaTime);
  transform->Translate(dir * speed * Time::deltaTime);
}

} // namespace Assteroids::Behaviours
