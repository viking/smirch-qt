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
  m_ui.serverTab->setFocus();
  connect(m_ui.serverTab, SIGNAL(inputReceived(const QString &, const QString &)),
      &inputHandler, SLOT(handleInput(const QString &, const QString &)));

  m_closeTimer.setSingleShot(true);
  connect(&m_closeTimer, SIGNAL(timeout()), this, SLOT(closeWindow()));
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
    connect(&inputHandler, SIGNAL(commandReady(IrcCommand *)),
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
  AbstractTab *tab = qobject_cast<AbstractTab *>(m_ui.tabWidget->currentWidget());
  if (tab == NULL) {
    tab = (AbstractTab *) m_ui.serverTab;
  }
  tab->noticeMessageReceived(message);
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
