#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "ui_mainwindow.h"
#include "abstracttab.h"
#include "session.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

  protected:
    void closeEvent(QCloseEvent *event);

  private slots:
    void on_actionConnect_triggered();
    void handleInput(const QString &text);
    void queryStarted(Query *query);
    void channelJoined(Channel *channel);
    void closeWindow();

  private:
    Ui::MainWindow m_ui;
    Session *m_session;
    QTimer m_closeTimer;
    QCloseEvent *m_closeEvent;

    void addTab(AbstractTab *tab, const QString &name);
    void closeSession();
};

#endif
