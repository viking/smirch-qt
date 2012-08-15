#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "session.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

  private slots:
    void on_actionConnect_triggered();
    void handleInput(const QString &text);
    void queryStarted(Query *query);
    void channelJoined(Channel *channel);

  private:
    Ui::MainWindow m_ui;
    Session *m_session;

    void addTab(Tab *tab, const QString &name);
};

#endif
