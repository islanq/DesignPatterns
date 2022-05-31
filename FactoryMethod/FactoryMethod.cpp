#include "Document.hpp"
#include "MyApplication.hpp"

auto main()->int
{
  /* Client's customization of the Framework */
  MyApplication app;

  app.NewDocument("foo");
  app.NewDocument("bar");
  app.ReportDocs();

  getchar();
  return EXIT_SUCCESS;
}
