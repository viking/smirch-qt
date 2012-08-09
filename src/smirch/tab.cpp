#include "tab.h"
#include <IrcCommand>

Tab::Tab(QWidget *parent)
  : QWidget(parent), m_type(ServerTab), m_session(NULL)
{
  ui.setupUi(this);
}

Tab::Tab(Type type, QWidget *parent)
  : QWidget(parent), m_type(type), m_session(NULL)
{
  ui.setupUi(this);
}

IrcSession *Tab::session()
{
  return m_session;
}

void Tab::setSession(IrcSession *session)
{
  if (m_session != NULL) {
    disconnect(m_session, 0, this, 0);
  }

  m_session = session;
  connect(m_session, SIGNAL(connecting()), this, SLOT(connecting()));
  connect(m_session, SIGNAL(connected()), this, SLOT(connected()));
  connect(m_session, SIGNAL(disconnected()), this, SLOT(disconnected()));
  connect(m_session, SIGNAL(messageReceived(IrcMessage *)), this, SLOT(messageReceived(IrcMessage *)));
  connect(m_session, SIGNAL(destroyed(QObject *)), this, SLOT(sessionDestroyed(QObject *)));
}

void Tab::setName(const QString &name)
{
  m_name = name;
}

void Tab::connecting()
{
  ui.textBrowser->append("Connecting...");
}

void Tab::connected()
{
  ui.textBrowser->append("Connected!");
}

void Tab::disconnected()
{
  ui.textBrowser->append("Disconnected.");
}

void Tab::messageReceived(IrcMessage *message)
{
  switch (m_type) {
    case ServerTab:
      switch (message->type()) {
        case IrcMessage::Join:
          if (message->isOwn()) {
            IrcJoinMessage *joinMessage = static_cast<IrcJoinMessage *>(message);
            emit channelJoined(joinMessage->channel());
          }
          break;
      }
      break;
    case ChannelTab:
      break;
    case QueryTab:
      break;
  }
}

void Tab::on_lineEdit_returnPressed()
{
  if (m_session != NULL) {
    QString s = ui.lineEdit->text();
    if (s.startsWith("/")) {
      IrcCommand *command = NULL;

      QStringList args = s.split(" ");
      QString commandName = args[0].right(args[0].length() - 1).toLower();
      if (commandName == "join") {
        command = IrcCommand::createJoin(args[1]);
      }

      if (command != NULL) {
        m_session->sendCommand(command);
      }
    }

    ui.lineEdit->clear();
  }
}

void Tab::sessionDestroyed(QObject *obj)
{
  if (obj == m_session) {
    m_session = NULL;
  }
}
