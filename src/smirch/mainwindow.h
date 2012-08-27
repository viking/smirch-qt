#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QShortcut>
#include <IrcMessage>
#include "ui_mainwindow.h"
#include "abstracttab.h"
#include "session.h"
#include "inputhandler.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

  protected:
    void closeEvent(QCloseEvent *event);

  private slots:
    void on_actionConnect_triggered();
    void queryStarted(Query *query);
    void channelJoined(Channel *channel);
    void closeWindow();
    void noticeMessageReceived(IrcNoticeMessage *message);
    void echoCommandReceived(const QString &text);
    void closeCommandReceived();

    void selectNextTab();
    void selectPreviousTab();
    void selectFirstTab();
    void selectSecondTab();
    void selectThirdTab();
    void selectFourthTab();
    void selectFifthTab();
    void selectSixthTab();
    void selectSeventhTab();
    void selectEighthTab();
    void selectNinthTab();

  private:
    Ui::MainWindow m_ui;
    Session *m_session;
    QTimer m_closeTimer;
    QCloseEvent *m_closeEvent;
    InputHandler inputHandler;

    QShortcut *m_nextTabShortcut;
    QShortcut *m_previousTabShortcut;
    QShortcut *m_firstTabShortcut;
    QShortcut *m_secondTabShortcut;
    QShortcut *m_thirdTabShortcut;
    QShortcut *m_fourthTabShortcut;
    QShortcut *m_fifthTabShortcut;
    QShortcut *m_sixthTabShortcut;
    QShortcut *m_seventhTabShortcut;
    QShortcut *m_eighthTabShortcut;
    QShortcut *m_ninthTabShortcut;

    void addTab(AbstractTab *tab, const QString &name);
    AbstractTab *currentTab();
    void closeSession();
    void selectTab(int index);
};

#endif
