#include "Bullet.h"
#include <Crow2D/components/colliders/CircleCollider.h>
#include <Crow2D/dataObjects/Sprite.h>
#include <SDL3/SDL_pixels.h>


namespace Assteroids::Behaviours {
using namespace Crow2D;
using namespace Crow2D::Components;
using namespace Crow2D::Types;

void Bullet::Awake() { SetupObject(); }
void Bullet::Update() { Move(); }

void Bullet::SetupObject() {
  gameObject->AddComponent<Renderer>(Primitives::Circle, Vector2(0.1f, 0.3f),
                                     SDL_Color{255, 0, 0, 255});
  CircleCollider &col = gameObject->AddComponent<CircleCollider>(0.3f);
  col.isTrigger = true;
}


void Bullet::Move() {
  transform->Translate(Vector3(transform->forward) * bulletspeed * Time::deltaTime);
}
} // namespace Assteroids::Behaviours
