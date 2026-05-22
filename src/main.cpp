#include "GameScene.h"
#include "Scenes/MainMenu/MainMenu.h"
#include <Crow2D/Crow2D.h>
#include <cstdio>

using namespace Assteroids;
using namespace Crow2D;
int main() {
  std::srand(time(NULL));
  Config::Init("Assteroids!");

  // MainMenu *mainMenu = new MainMenu();
  // Engine::Run(*mainMenu);

  GameScene *gameScene = new GameScene();
  Engine::Run(*gameScene);
  printf("Bye bye!\n");
}
