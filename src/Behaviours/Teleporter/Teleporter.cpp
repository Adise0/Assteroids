#include "Teleporter.h"
#include <Crow2D/dataObjects/Vectors.h>
#include <cstdio>
#include <stdexcept>


namespace Assteroids::Behaviours {

using namespace Crow2D;
using namespace Crow2D::Types;
using namespace Crow2D::Components;

void Teleporter::Update() { CheckBounds(); }


void Teleporter::CheckBounds() {
  if (!Camera::activeCamera) return;

  Vector2 pos = Vector2(transform->position);

  bool isOutside = false;

  if (pos.x < Camera::activeCamera->rect.get().Left()) {
    pos.x = Camera::activeCamera->rect.get().Right();
    isOutside = true;
  }
  if (pos.x > Camera::activeCamera->rect.get().Right()) {
    pos.x = Camera::activeCamera->rect.get().Left();
    isOutside = true;
  }
  if (pos.y < Camera::activeCamera->rect.get().Bottom()) {
    pos.y = Camera::activeCamera->rect.get().Top();
    isOutside = true;
  }
  if (pos.y > Camera::activeCamera->rect.get().Top()) {
    pos.y = Camera::activeCamera->rect.get().Bottom();
    isOutside = true;
  }

  if (!hasBeenInsideOnce && !isOutside) hasBeenInsideOnce = true;
  if (!hasBeenInsideOnce) return;

  if (pos != Vector2(transform->position)) transform->position = Vector3(pos);
}


} // namespace Assteroids::Behaviours
