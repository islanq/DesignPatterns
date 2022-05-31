#include "VisitorBase.hpp"


using namespace visitor;

auto main(int argc, char *argv[])->int
{
  infotype::Run();
  cout << "\n\n";
  primary::Run();
  cout << "\n\n";
  before::Run();
  cout << "\n\n";
  after::Run();


  getchar();
  return EXIT_SUCCESS;
}
