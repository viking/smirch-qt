#include <IrcCommand>
#include <IrcUtil>
#include "abstracttab.h"

AbstractTab::AbstractTab(QWidget *parent)
  : QWidget(parent), m_conversation(NULL)
{
}

AbstractTab::AbstractTab(Conversation *conversation, QWidget *parent)
  : QWidget(parent), m_conversation(conversation)
{
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
  IrcSender s = message->sender();
  appendText(QString("* %1 (%2@%3) has joined %4").
      arg(s.name()).arg(s.user()).arg(s.host()).arg(message->channel()));
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
  QStringList parameters = message->parameters();
  parameters.removeFirst();
  appendText(parameters.join(" "));
}

void AbstractTab::partMessageReceived(IrcPartMessage *message)
{
  IrcSender s = message->sender();
  QString str = QString("* %1 (%2@%3) has left %4").
      arg(s.name()).arg(s.user()).arg(s.host()).arg(message->channel());

  if (!message->reason().isEmpty()) {
    str.append(QString(" (%1)").arg(message->reason()));
  }

  appendText(str);
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
  if (message->isAction()) {
    appendText(QString("* %1 %2").arg(message->sender().name()).
        arg(IrcUtil::messageToHtml(message->message())));
  }
  else {
    appendText(QString("<%1> %2").arg(message->sender().name()).
        arg(IrcUtil::messageToHtml(message->message())));
  }
}

void AbstractTab::quitMessageReceived(IrcQuitMessage *message)
{
  if (!message->reason().isEmpty()) {
    appendText(QString("* %1 has quit (%2)").arg(message->sender().name()).
        arg(message->reason()));
  }
  else {
    appendText(QString("* %1 has quit").arg(message->sender().name()));
  }
}

void AbstractTab::topicMessageReceived(IrcTopicMessage *message)
{
  QByteArray data = message->toData();
  appendText(QString(data));
}

void AbstractTab::handleInput()
{
  QLineEdit *widget = lineEdit();
  QString text = widget->text();
  emit textEntered(text);
  widget->clear();
}

void AbstractTab::appendText(QString text)
{
  QTextEdit *widget = textEdit();
  widget->append(text);
}
