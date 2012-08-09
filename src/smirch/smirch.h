#ifndef __SMIRCH_H
#define __SMIRCH_H

#include <QApplication>
#include <QMainWindow>
#include "mainwindow.h"

class Smirch : public QApplication
{
  Q_OBJECT

  public:
    Smirch(int &argc, char **argv);

  private:
    MainWindow *window;
};

#endif
