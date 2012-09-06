#include <IrcCommand>
#include <IrcUtil>
#include <QDateTime>
#include <QShortcut>
#include "abstracttab.h"
#include "messageformatter.h"
#include "session.h"
#include <QtDebug>

AbstractTab::AbstractTab(QWidget *parent)
  : QWidget(parent), m_conversation(NULL), m_messageNumber(1)
{
}

AbstractTab::AbstractTab(Conversation *conversation, QWidget *parent)
  : QWidget(parent), m_conversation(conversation), m_messageNumber(1)
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
  connect(m_conversation, SIGNAL(capabilityMessageReceived(IrcCapabilityMessage *)),
      this, SLOT(capabilityMessageReceived(IrcCapabilityMessage *)));
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

void AbstractTab::appendMessage(QString text)
{
  webView()->appendHtml(text);
}

void AbstractTab::setFont(const QFont &font)
{
  webView()->setFont(font);
}

void AbstractTab::echoReceived(const QString &text)
{
  appendMessage(MessageFormatter::formatEcho(m_messageNumber++, text));
}

void AbstractTab::on_lineEdit_returnPressed()
{
  LineEdit *widget = lineEdit();
  QString text = widget->text();
  emit inputReceived(recipient(), text);
  widget->clear();
}

void AbstractTab::connecting()
{
  Session *session = qobject_cast<Session *>(QObject::sender());
  if (session != NULL) {
    appendMessage(MessageFormatter::formatConnecting(m_messageNumber++,
          session->host()));
  }
}

void AbstractTab::connected()
{
  Session *session = qobject_cast<Session *>(QObject::sender());
  if (session != NULL) {
    appendMessage(MessageFormatter::formatConnected(m_messageNumber++,
          session->host()));
  }
}

void AbstractTab::disconnected()
{
  appendMessage(MessageFormatter::formatDisconnected(m_messageNumber++));
}

void AbstractTab::unknownMessageReceived(IrcMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::errorMessageReceived(IrcErrorMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::inviteMessageReceived(IrcInviteMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::joinMessageReceived(IrcJoinMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::kickMessageReceived(IrcKickMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::modeMessageReceived(IrcModeMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::nickMessageReceived(IrcNickMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::noticeMessageReceived(IrcNoticeMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::numericMessageReceived(IrcNumericMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::partMessageReceived(IrcPartMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::pingMessageReceived(IrcPingMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::pongMessageReceived(IrcPongMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::privateMessageReceived(IrcPrivateMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::quitMessageReceived(IrcQuitMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::topicMessageReceived(IrcTopicMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::capabilityMessageReceived(IrcCapabilityMessage *message)
{
  appendMessage(MessageFormatter::format(message, m_messageNumber++));
}

void AbstractTab::closeEvent(QCloseEvent *event)
{
  m_conversation->close();
  event->accept();
}
