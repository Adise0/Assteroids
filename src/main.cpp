#include "Scenes/SampleScene/SampleScene.h"
#include <Crow2D/Crow2D.h>
#include <cstdio>

using namespace Template;
using namespace Crow2D;
int main() {
  std::srand(time(NULL));
  Config::Init("Template!");

  SampleScene *sampleScene = new SampleScene();
  Engine::Run(*sampleScene);
  printf("Bye bye!\n");
}
