#include <IrcCommand>
#include <IrcUtil>
#include <QDateTime>
#include "abstracttab.h"
#include <QtDebug>

const QString AbstractTab::s_messageMarkup = QString("    <div id=\"message-%1\" class=\"message\"><span class=\"timestamp\">[%2]</span> %3</div>\n");

AbstractTab::AbstractTab(QWidget *parent)
  : QWidget(parent), m_conversation(NULL), m_pageLoaded(false), m_messageNumber(1)
{
}

AbstractTab::AbstractTab(Conversation *conversation, QWidget *parent)
  : QWidget(parent), m_conversation(conversation), m_pageLoaded(false), m_messageNumber(1)
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
  appendMessage("Connecting...");
}

void AbstractTab::connected()
{
  appendMessage("Connected!");
}

void AbstractTab::disconnected()
{
  appendMessage("Disconnected.");
}

void AbstractTab::unknownMessageReceived(IrcMessage *message)
{
  QByteArray data = message->toData();
  appendMessage(QString(data));
}

void AbstractTab::errorMessageReceived(IrcErrorMessage *message)
{
  QByteArray data = message->toData();
  appendMessage(QString(data));
}

void AbstractTab::inviteMessageReceived(IrcInviteMessage *message)
{
  QByteArray data = message->toData();
  appendMessage(QString(data));
}

void AbstractTab::joinMessageReceived(IrcJoinMessage *message)
{
  IrcSender s = message->sender();
  appendMessage(QString("* %1 (%2@%3) has joined %4").
      arg(s.name()).arg(s.user()).arg(s.host()).arg(message->channel()));
}

void AbstractTab::kickMessageReceived(IrcKickMessage *message)
{
  QByteArray data = message->toData();
  appendMessage(QString(data));
}

void AbstractTab::modeMessageReceived(IrcModeMessage *message)
{
  QByteArray data = message->toData();
  appendMessage(QString(data));
}

void AbstractTab::nickMessageReceived(IrcNickMessage *message)
{
  QByteArray data = message->toData();
  appendMessage(QString(data));
}

void AbstractTab::noticeMessageReceived(IrcNoticeMessage *message)
{
  QByteArray data = message->toData();
  appendMessage(QString(data));
}

void AbstractTab::numericMessageReceived(IrcNumericMessage *message)
{
  QStringList parameters = message->parameters();
  parameters.removeFirst();
  appendMessage(QString("(%1) %2").arg(message->code()).
      arg(parameters.join(" ")));
}

void AbstractTab::partMessageReceived(IrcPartMessage *message)
{
  IrcSender s = message->sender();
  QString str = QString("* %1 (%2@%3) has left %4").
      arg(s.name()).arg(s.user()).arg(s.host()).arg(message->channel());

  if (!message->reason().isEmpty()) {
    str.append(QString(" (%1)").arg(message->reason()));
  }

  appendMessage(str);
}

void AbstractTab::pingMessageReceived(IrcPingMessage *message)
{
  QByteArray data = message->toData();
  appendMessage(QString(data));
}

void AbstractTab::pongMessageReceived(IrcPongMessage *message)
{
  QByteArray data = message->toData();
  appendMessage(QString(data));
}

void AbstractTab::privateMessageReceived(IrcPrivateMessage *message)
{
  if (message->isAction()) {
    appendMessage(QString("* %1 %2").arg(message->sender().name()).
        arg(IrcUtil::messageToHtml(message->message())));
  }
  else {
    appendMessage(QString("<%1> %2").arg(message->sender().name()).
        arg(IrcUtil::messageToHtml(message->message())));
  }
}

void AbstractTab::quitMessageReceived(IrcQuitMessage *message)
{
  if (!message->reason().isEmpty()) {
    appendMessage(QString("* %1 has quit (%2)").arg(message->sender().name()).
        arg(message->reason()));
  }
  else {
    appendMessage(QString("* %1 has quit").arg(message->sender().name()));
  }
}

void AbstractTab::topicMessageReceived(IrcTopicMessage *message)
{
  QByteArray data = message->toData();
  appendMessage(QString(data));
}

void AbstractTab::handleInput()
{
  QLineEdit *widget = lineEdit();
  QString text = widget->text();
  emit inputReceived(recipient(), text);
  widget->clear();
}

void AbstractTab::appendMessage(QString text)
{
  m_appendMutex.lock();
  if (m_pageLoaded) {
    m_appendMutex.unlock();
    internalAppendMessage(text);
  }
  else {
    //qDebug() << "Page not loaded yet, appending:" << text;
    m_appendQueue << text;
    m_appendMutex.unlock();
  }
}

void AbstractTab::internalAppendMessage(const QString &text)
{
  QWebView *widget = webView();
  QWebFrame *frame = widget->page()->mainFrame();
  if (m_body.isNull()) {
    m_body = frame->findFirstElement("body");
  }

  m_body.appendInside(s_messageMarkup.arg(m_messageNumber++).
      arg(QDateTime::currentDateTime().toString("hh:mm")).
      arg(text));
  QWebElement element = m_body.lastChild();
  frame->scrollToAnchor(element.attribute("id"));
}

void AbstractTab::on_webView_loadFinished(bool ok)
{
  m_appendMutex.lock();
  m_pageLoaded = true;
  for (int i = 0; i < m_appendQueue.count(); i++) {
    internalAppendMessage(m_appendQueue.at(i));
  }
  m_appendQueue.clear();
  m_appendMutex.unlock();
}
