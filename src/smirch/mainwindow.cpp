#include <IrcCommand>
#include "mainwindow.h"
#include "connectdialog.h"
#include "tab.h"
#include "channeltab.h"

#include <QtDebug>

#define CLOSE_TIMEOUT 3000

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), m_session(NULL), m_closeEvent(NULL)
{
  m_ui.setupUi(this);

  connect(m_ui.serverTab, SIGNAL(inputReceived(const QString &, const QString &)),
      &inputHandler, SLOT(handleInput(const QString &, const QString &)));
  connect(&inputHandler, SIGNAL(echoCommandReceived(const QString &)),
      this, SLOT(echoCommandReceived(const QString &)));
  connect(&inputHandler, SIGNAL(closeCommandReceived()),
      this, SLOT(closeCommandReceived()));

  m_closeTimer.setSingleShot(true);
  connect(&m_closeTimer, SIGNAL(timeout()), this, SLOT(closeWindow()));

  m_nextTabShortcut = new QShortcut(QKeySequence("Ctrl+PgDown"), this);
  m_previousTabShortcut = new QShortcut(QKeySequence("Ctrl+PgUp"), this);
  m_firstTabShortcut = new QShortcut(QKeySequence("Alt+1"), this);
  m_secondTabShortcut = new QShortcut(QKeySequence("Alt+2"), this);
  m_thirdTabShortcut = new QShortcut(QKeySequence("Alt+3"), this);
  m_fourthTabShortcut = new QShortcut(QKeySequence("Alt+4"), this);
  m_fifthTabShortcut = new QShortcut(QKeySequence("Alt+5"), this);
  m_sixthTabShortcut = new QShortcut(QKeySequence("Alt+6"), this);
  m_seventhTabShortcut = new QShortcut(QKeySequence("Alt+7"), this);
  m_eighthTabShortcut = new QShortcut(QKeySequence("Alt+8"), this);
  m_ninthTabShortcut = new QShortcut(QKeySequence("Alt+9"), this);
  connect(m_nextTabShortcut, SIGNAL(activated()), this, SLOT(selectNextTab()));
  connect(m_previousTabShortcut, SIGNAL(activated()), this, SLOT(selectPreviousTab()));
  connect(m_firstTabShortcut, SIGNAL(activated()), this, SLOT(selectFirstTab()));
  connect(m_secondTabShortcut, SIGNAL(activated()), this, SLOT(selectSecondTab()));
  connect(m_thirdTabShortcut, SIGNAL(activated()), this, SLOT(selectThirdTab()));
  connect(m_fourthTabShortcut, SIGNAL(activated()), this, SLOT(selectFourthTab()));
  connect(m_fifthTabShortcut, SIGNAL(activated()), this, SLOT(selectFifthTab()));
  connect(m_sixthTabShortcut, SIGNAL(activated()), this, SLOT(selectSixthTab()));
  connect(m_seventhTabShortcut, SIGNAL(activated()), this, SLOT(selectSeventhTab()));
  connect(m_eighthTabShortcut, SIGNAL(activated()), this, SLOT(selectEighthTab()));
  connect(m_ninthTabShortcut, SIGNAL(activated()), this, SLOT(selectNinthTab()));

  m_ui.serverTab->setFocus();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (m_session != NULL && m_session->isActive()) {
    /* Close out the session first */
    qDebug() << "Quitting...";
    m_closeEvent = event;
    connect(m_session, SIGNAL(disconnected()), this, SLOT(closeWindow()));
    m_session->sendCommand(IrcCommand::createQuit("Quitting..."));
    m_closeTimer.start(CLOSE_TIMEOUT);
  }
  else {
    QMainWindow::closeEvent(event);
  }
}

void MainWindow::on_actionConnect_triggered()
{
  ConnectDialog dialog(this);
  dialog.exec();

  if (dialog.result() == QDialog::Accepted) {
    if (m_session != NULL) {
      m_session->close();
      for (int i = m_ui.tabWidget->count() - 1; i > 1; i--) {
        QWidget *widget = m_ui.tabWidget->widget(i);
        m_ui.tabWidget->removeTab(i);
        widget->deleteLater();
      }
      disconnect(m_session, 0, 0, 0);
      disconnect(&inputHandler, 0, m_session, 0);
      m_session->deleteLater();
      m_session = NULL;
    }

    m_session = new Session(this);
    m_session->setHost(dialog.server());
    m_session->setPort(dialog.port());
    m_session->setUserName(dialog.username());
    m_session->setNickName(dialog.nickname());
    m_session->setRealName(dialog.realName());
    m_session->setNickPassword(dialog.nickPassword());

    connect(m_session, SIGNAL(serverNumericMessageReceived(IrcNumericMessage *)),
        m_ui.serverTab, SLOT(numericMessageReceived(IrcNumericMessage *)));
    connect(m_session, SIGNAL(serverCapabilityMessageReceived(IrcCapabilityMessage *)),
        m_ui.serverTab, SLOT(capabilityMessageReceived(IrcCapabilityMessage *)));

    connect(m_session, SIGNAL(connecting()),
        m_ui.serverTab, SLOT(connecting()));
    connect(m_session, SIGNAL(connected()),
        m_ui.serverTab, SLOT(connected()));
    connect(m_session, SIGNAL(disconnected()),
        m_ui.serverTab, SLOT(disconnected()));
    connect(m_session, SIGNAL(channelJoined(Channel *)),
        this, SLOT(channelJoined(Channel *)));
    connect(m_session, SIGNAL(queryStarted(Query *)),
        this, SLOT(queryStarted(Query *)));

    connect(&inputHandler, SIGNAL(ircCommandReceived(IrcCommand *)),
        m_session, SLOT(handleCommand(IrcCommand *)));

    connect(m_session, SIGNAL(noticeMessageReceived(IrcNoticeMessage *)),
        this, SLOT(noticeMessageReceived(IrcNoticeMessage *)));

    m_session->open();
  }
}

void MainWindow::queryStarted(Query *query)
{
  Tab *tab = new Tab(query);
  addTab(tab, query->person()->name());
}

void MainWindow::channelJoined(Channel *channel)
{
  ChannelTab *tab = new ChannelTab(channel);
  addTab(tab, channel->name());
}

void MainWindow::closeWindow()
{
  m_closeTimer.stop();
  if (m_session != NULL) {
    if (m_session->isActive()) {
      qDebug() << "Forced close!";
      m_session->close();
    }
  }
  QMainWindow::closeEvent(m_closeEvent);
}

void MainWindow::noticeMessageReceived(IrcNoticeMessage *message)
{
  AbstractTab *tab = currentTab();
  if (tab == NULL) {
    tab = (AbstractTab *) m_ui.serverTab;
  }
  tab->noticeMessageReceived(message);
}

void MainWindow::echoCommandReceived(const QString &text)
{
  AbstractTab *tab = currentTab();
  if (tab == NULL) {
    tab = (AbstractTab *) m_ui.serverTab;
  }
  tab->echoReceived(text);
}

void MainWindow::closeCommandReceived()
{
  AbstractTab *tab = currentTab();
  if (tab != NULL) {
    if (tab == m_ui.serverTab) {
      close();
    }
    else {
      m_ui.tabWidget->removeTab(m_ui.tabWidget->currentIndex());
      tab->close();
    }
  }
}

void MainWindow::selectNextTab()
{
  int i = m_ui.tabWidget->currentIndex();
  if (i < (m_ui.tabWidget->count() - 1)) {
    m_ui.tabWidget->setCurrentIndex(i + 1);
  }
}

void MainWindow::selectPreviousTab()
{
  int i = m_ui.tabWidget->currentIndex();
  if (i > 0) {
    m_ui.tabWidget->setCurrentIndex(i - 1);
  }
}

void MainWindow::selectFirstTab()
{
  selectTab(0);
}

void MainWindow::selectSecondTab()
{
  selectTab(1);
}

void MainWindow::selectThirdTab()
{
  selectTab(2);
}

void MainWindow::selectFourthTab()
{
  selectTab(3);
}

void MainWindow::selectFifthTab()
{
  selectTab(4);
}

void MainWindow::selectSixthTab()
{
  selectTab(5);
}

void MainWindow::selectSeventhTab()
{
  selectTab(6);
}

void MainWindow::selectEighthTab()
{
  selectTab(7);
}

void MainWindow::selectNinthTab()
{
  selectTab(8);
}

void MainWindow::selectTab(int index)
{
  if (m_ui.tabWidget->count() > index) {
    m_ui.tabWidget->setCurrentIndex(index);
  }
}

void MainWindow::addTab(AbstractTab *tab, const QString &name)
{
  connect(tab, SIGNAL(inputReceived(const QString &, const QString &)),
      &inputHandler, SLOT(handleInput(const QString &, const QString &)));
  connect(m_session, SIGNAL(connecting()),
      tab, SLOT(connecting()));
  connect(m_session, SIGNAL(connected()),
      tab, SLOT(connected()));
  connect(m_session, SIGNAL(disconnected()),
      tab, SLOT(disconnected()));

  m_ui.tabWidget->addTab(tab, name);
  m_ui.tabWidget->setCurrentIndex(m_ui.tabWidget->count() - 1);
}

AbstractTab *MainWindow::currentTab()
{
  return qobject_cast<AbstractTab *>(m_ui.tabWidget->currentWidget());
}
