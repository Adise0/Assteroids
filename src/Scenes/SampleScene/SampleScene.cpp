

#include "SampleScene.h"
#include <Crow2D/Crow2dUtils.h>
#include <Crow2D/components/Renderer.h>
#include <Crow2D/dataObjects/Sprite.h>
#include <cstdio>

namespace Template {

using namespace Crow2D;
using namespace Crow2D::Scenes;
using namespace Crow2D::Components;
using namespace Crow2D::Types;
using namespace Crow2D::Rendering;


SampleScene::SampleScene() : Scene("Sample Scene") {}

void SampleScene::Load() { LoadUI(); }

void SampleScene::LoadUI() {

  GameObject &uiHolderGO = rootGameObject->CreateChild("UI Holder");
  Camera &cam = uiHolderGO.AddComponent<Camera>();
  cam.SetAsActiveCamera();
  UIRenderer &mainRenderer = uiHolderGO.AddComponent<UIRenderer>("ui/samples/index.html");
}
} // namespace Template

