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

  m_closeTimer.setSingleShot(true);
  connect(&m_closeTimer, SIGNAL(timeout()), this, SLOT(closeWindow()));
  connect(m_ui.serverTab, SIGNAL(textEntered(const QString &)),
      this, SLOT(handleInput(const QString &)));
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

    m_session->open();
  }
}

void MainWindow::handleInput(const QString &text)
{
  if (m_session != NULL) {
    IrcCommand *command = NULL;
    if (text.startsWith("/")) {
      QString commandName = text.section(" ", 0, 0).mid(1).toLower();
      QString predicate = text.section(" ", 1);
      if (commandName == "join") {
        QStringList args = predicate.split(" ");
        command = IrcCommand::createJoin(args[0]);
      }
      else if (commandName == "quit") {
        command = IrcCommand::createQuit(predicate);
      }
    }
    if (command == NULL) {
      qDebug() << "Unknown command:" << text;
    }
    else {
      m_session->sendCommand(command);
    }
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

void MainWindow::addTab(AbstractTab *tab, const QString &name)
{
  connect(tab, SIGNAL(textEntered(const QString &)),
      this, SLOT(handleInput(const QString &)));
  connect(m_session, SIGNAL(connecting()),
      tab, SLOT(connecting()));
  connect(m_session, SIGNAL(connected()),
      tab, SLOT(connected()));
  connect(m_session, SIGNAL(disconnected()),
      tab, SLOT(disconnected()));

  m_ui.tabWidget->addTab(tab, name);
  m_ui.tabWidget->setCurrentIndex(m_ui.tabWidget->count() - 1);
}
