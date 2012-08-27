#include "smirch.h"

Smirch::Smirch(int &argc, char **argv)
  : QApplication(argc, argv)
{
  setOrganizationName("pillageandplunder");
  setOrganizationDomain("pillageandplunder.net");
  setApplicationName("smirch");

  m_window = new MainWindow();
  m_window->show();
}
