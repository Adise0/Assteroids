#include "Scenes/MainMenu/MainMenu.h"
#include <Crow2D/Crow2D.h>
#include <cstdio>

using namespace Template;
using namespace Crow2D;
int main() {
  std::srand(time(NULL));
  Config::Init("Template!");

  MainMenu *mainMenu = new MainMenu();
  Engine::Run(*mainMenu);
  printf("Bye bye!\n");
}
