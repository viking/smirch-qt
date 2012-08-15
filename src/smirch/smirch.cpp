#include "smirch.h"

Smirch::Smirch(int &argc, char **argv)
  : QApplication(argc, argv)
{
  m_window = new MainWindow();
  m_window->show();
}
