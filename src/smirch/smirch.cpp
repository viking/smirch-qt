#include "smirch.h"

Smirch::Smirch(int &argc, char **argv)
  : QApplication(argc, argv)
{
  window = new MainWindow();
  window->show();
}
