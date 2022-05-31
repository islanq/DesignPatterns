#include <iostream>
#include <string>
#include "Commander.h"
#include "Commander2.h"


auto main()->int
{
  commander::example::Run();
  commander::example2::Run();

  getchar();
  return EXIT_SUCCESS;
}
