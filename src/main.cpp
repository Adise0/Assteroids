#include "Scenes/MainMenu/MainMenu.h"
#include <Crow2D/Crow2D.h>
#include <cstdio>

using namespace Assteroids;
using namespace Crow2D;
int main() {
  std::srand(time(NULL));
  Config::Init("Assteroids!");

  MainMenu *mainMenu = new MainMenu();
  Engine::Run(*mainMenu);
  printf("Bye bye!\n");
}
