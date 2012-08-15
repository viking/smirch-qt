#include "abstracttab.h"
#include <IrcCommand>

AbstractTab::AbstractTab(QWidget *parent)
  : QWidget(parent), m_conversation(NULL), m_uiInitialized(false)
{
}

AbstractTab::AbstractTab(Conversation *conversation, QWidget *parent)
  : QWidget(parent), m_conversation(conversation), m_uiInitialized(false)
{
  // FIXME: This creates a race condition if the UI is not initialized
  // before one of these signals are emitted. The current workaround
  // (using m_uiInitialized) is not the best.
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

QString AbstractTab::recipient() const
{
  if (m_conversation != NULL) {
    return m_conversation->recipient();
  }
  else {
    return QString();
  }
}

void AbstractTab::connecting()
{
  appendText("Connecting...");
}

void AbstractTab::connected()
{
  appendText("Connected!");
}

void AbstractTab::disconnected()
{
  appendText("Disconnected.");
}

void AbstractTab::unknownMessageReceived(IrcMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::errorMessageReceived(IrcErrorMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::inviteMessageReceived(IrcInviteMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::joinMessageReceived(IrcJoinMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::kickMessageReceived(IrcKickMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::modeMessageReceived(IrcModeMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::nickMessageReceived(IrcNickMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::noticeMessageReceived(IrcNoticeMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::numericMessageReceived(IrcNumericMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::partMessageReceived(IrcPartMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::pingMessageReceived(IrcPingMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::pongMessageReceived(IrcPongMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::privateMessageReceived(IrcPrivateMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::quitMessageReceived(IrcQuitMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::topicMessageReceived(IrcTopicMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}
