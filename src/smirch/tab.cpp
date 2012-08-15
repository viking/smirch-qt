#include "tab.h"
#include <IrcCommand>

Tab::Tab(QWidget *parent)
  : QWidget(parent), m_conversation(NULL)
{
  m_ui.setupUi(this);
}

Tab::Tab(Conversation *conversation, QWidget *parent)
  : QWidget(parent), m_conversation(conversation)
{
  m_ui.setupUi(this);

  connect(m_conversation, SIGNAL(unknownMessageReceived(IrcMessage *)),
      this, SLOT(unknownMessageReceived(IrcMessage *)));
  connect(m_conversation, SIGNAL(errorMessageReceived(IrcErrorMessage *)),
      this, SLOT(errorMessageReceived(IrcErrorMessage *)));
  connect(m_conversation, SIGNAL(inviteMessageReceived(IrcInviteMessage *)),
      this, SLOT(inviteMessageReceived(IrcInviteMessage *)));
  connect(m_conversation, SIGNAL(joinMessageReceived(IrcJoinMessage *)),
      this, SLOT(joinMessageReceived(IrcJoinMessage *)));
  connect(m_conversation, SIGNAL(kickMessageReceived(IrcKickMessage *)),
      this, SLOT(kickMessageReceived(IrcKickMessage *)));
  connect(m_conversation, SIGNAL(modeMessageReceived(IrcModeMessage *)),
      this, SLOT(modeMessageReceived(IrcModeMessage *)));
  connect(m_conversation, SIGNAL(nickMessageReceived(IrcNickMessage *)),
      this, SLOT(nickMessageReceived(IrcNickMessage *)));
  connect(m_conversation, SIGNAL(noticeMessageReceived(IrcNoticeMessage *)),
      this, SLOT(noticeMessageReceived(IrcNoticeMessage *)));
  connect(m_conversation, SIGNAL(numericMessageReceived(IrcNumericMessage *)),
      this, SLOT(numericMessageReceived(IrcNumericMessage *)));
  connect(m_conversation, SIGNAL(partMessageReceived(IrcPartMessage *)),
      this, SLOT(partMessageReceived(IrcPartMessage *)));
  connect(m_conversation, SIGNAL(pingMessageReceived(IrcPingMessage *)),
      this, SLOT(pingMessageReceived(IrcPingMessage *)));
  connect(m_conversation, SIGNAL(pongMessageReceived(IrcPongMessage *)),
      this, SLOT(pongMessageReceived(IrcPongMessage *)));
  connect(m_conversation, SIGNAL(privateMessageReceived(IrcPrivateMessage *)),
      this, SLOT(privateMessageReceived(IrcPrivateMessage *)));
  connect(m_conversation, SIGNAL(quitMessageReceived(IrcQuitMessage *)),
      this, SLOT(quitMessageReceived(IrcQuitMessage *)));
  connect(m_conversation, SIGNAL(topicMessageReceived(IrcTopicMessage *)),
      this, SLOT(topicMessageReceived(IrcTopicMessage *)));
}

const QString &Tab::recipient()
{
  if (m_conversation != NULL) {
    return m_conversation->recipient();
  }
  else {
    return QString();
  }
}

void Tab::connecting()
{
  m_ui.textBrowser->append("Connecting...");
}

void Tab::connected()
{
  m_ui.textBrowser->append("Connected!");
}

void Tab::disconnected()
{
  m_ui.textBrowser->append("Disconnected.");
}

void Tab::unknownMessageReceived(IrcMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::errorMessageReceived(IrcErrorMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::inviteMessageReceived(IrcInviteMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::joinMessageReceived(IrcJoinMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::kickMessageReceived(IrcKickMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::modeMessageReceived(IrcModeMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::nickMessageReceived(IrcNickMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::noticeMessageReceived(IrcNoticeMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::numericMessageReceived(IrcNumericMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::partMessageReceived(IrcPartMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::pingMessageReceived(IrcPingMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::pongMessageReceived(IrcPongMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::privateMessageReceived(IrcPrivateMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::quitMessageReceived(IrcQuitMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::topicMessageReceived(IrcTopicMessage *message)
{
  QByteArray data = message->toData();
  m_ui.textBrowser->append(QString(data));
}

void Tab::on_lineEdit_returnPressed()
{
  QString text = m_ui.lineEdit->text();
  emit textEntered(text);
  m_ui.lineEdit->clear();
}
