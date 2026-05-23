#include "GameScene.h"
#include "Scenes/MainMenu/MainMenu.h"
#include "Stats.h"
#include <Crow2D/Crow2D.h>
#include <cstdio>

using namespace Assteroids;
using namespace Crow2D;
int main() {
  std::srand(time(NULL));
  Config::Init("Assteroids!");

  new Data::Stats();

  MainMenu *mainMenu = new MainMenu();
  Engine::Run(*mainMenu);

  printf("Bye bye!\n");
}
