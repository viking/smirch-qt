#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

  private slots:
    void on_actionConnect_triggered();
    void on_serverTab_channelJoined(const QString &name);

  private:
    Ui::MainWindow ui;
};

#endif
