#include <IrcCommand>
#include "mainwindow.h"
#include "connectdialog.h"

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), m_session(NULL)
{
  m_ui.setupUi(this);

  connect(m_ui.serverTab, SIGNAL(textEntered(const QString &)),
      this, SLOT(handleInput(const QString &)));
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
    qDebug() << "Handle:" << text;
    if (text.startsWith("/")) {
      IrcCommand *command = NULL;

      QString commandName = text.section(" ", 0, 0).mid(1).toLower();
      QString predicate = text.section(" ", 1);
      if (commandName == "join") {
        QStringList args = predicate.split(" ");
        command = IrcCommand::createJoin(args[0]);
      }
      else if (commandName == "quit") {
        command = IrcCommand::createQuit(predicate);
      }

      if (command != NULL) {
        qDebug() << "Sending:" << command->toString();
        m_session->sendCommand(command);
      }
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
  Tab *tab = new Tab(channel);
  addTab(tab, channel->name());
}

void MainWindow::addTab(Tab *tab, const QString &name)
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
