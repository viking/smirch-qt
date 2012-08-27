#include "session.h"

#include <QtDebug>

Session::Session(QObject *parent)
  : IrcSession(parent)
{
  connect(this, SIGNAL(messageReceived(IrcMessage *)),
      this, SLOT(handleMessage(IrcMessage *)));
}

void Session::setNickPassword(const QString &nickPassword)
{
  m_nickPassword = nickPassword;
  if (m_nickPassword.isEmpty()) {
    disconnect(this, SIGNAL(password(QString *)),
        this, SLOT(sendPassword(QString *)));
  }
  else {
    connect(this, SIGNAL(password(QString *)),
        this, SLOT(sendPassword(QString *)));
  }
}

void Session::sendPassword(QString *password)
{
  /* Sanity check */
  if (!m_nickPassword.isEmpty()) {
    *password = QString("%1:%2").arg(nickName()).arg(m_nickPassword);
  }
}

void Session::handleMessage(IrcMessage *message)
{
  Conversation *conversation = NULL;

  m_mutex.lock();
  for (int i = 0; i < m_conversations.size(); i++) {
    Conversation *c = m_conversations[i];
    if (c->includes(message)) {
      conversation = c;
      break;
    }
  }
  m_mutex.unlock();

  if (conversation == NULL) {
    switch (message->type()) {
      case IrcMessage::Join:
        {
          IrcJoinMessage *m = static_cast<IrcJoinMessage *>(message);

          if (m->isOwn()) {
            m_mutex.lock();
            Channel *channel = createChannel(m->channel());
            emit channelJoined(channel);
            m_mutex.unlock();

            conversation = (Conversation *) channel;
          }
        }
        break;

      case IrcMessage::Numeric:
        {
          IrcNumericMessage *m = static_cast<IrcNumericMessage *>(message);
          emit serverNumericMessageReceived(m);
        }
        break;

      case IrcMessage::Private:
        {
          IrcPrivateMessage *m = static_cast<IrcPrivateMessage *>(message);
          Person *person = NULL;
          if (m->isOwn()) {
            person = new Person(m->target(), this);
          }
          else {
            person = new Person(m->sender(), this);
          }

          m_mutex.lock();
          Query *query = createQuery(person);
          emit queryStarted(query);
          m_mutex.unlock();

          conversation = (Conversation *) query;
        }
        break;

      case IrcMessage::Notice:
        {
          IrcNoticeMessage *m = static_cast<IrcNoticeMessage *>(message);
          if (m->target() == nickName()) {
            emit noticeMessageReceived(m);
          }
        }

      case IrcMessage::Capability:
        {
          IrcCapabilityMessage *m = static_cast<IrcCapabilityMessage *>(message);
          if (m->isValid() && !m->capabilities().isEmpty()) {
            emit serverCapabilityMessageReceived(m);
          }
        }
        break;

      default:
        break;
    }
  }

  if (conversation != NULL) {
    conversation->handleMessage(message);
  }
}

void Session::handleCommand(IrcCommand *command)
{
  IrcMessage *message = NULL;
  if (command->type() == IrcCommand::Message) {
    message = IrcMessage::fromCommand(nickName(), command, this);
  }

  //qDebug() << "Sending command:" << command->toString();
  if (sendCommand(command)) {
    if (message != NULL) {
      handleMessage(message);
    }
  }
  else {
    qDebug() << "Failed to send command:" << command->toString();
  }
}

void Session::channelClosed()
{
  Channel *channel = qobject_cast<Channel *>(QObject::sender());
  if (channel != NULL) {
    sendCommand(IrcCommand::createPart(channel->name()));
    removeConversation(channel);
  }
}

void Session::queryClosed()
{
  Query *query = qobject_cast<Query *>(QObject::sender());
  if (query != NULL) {
    removeConversation(query);
  }
}

Query *Session::createQuery(Person *person)
{
  Query *query = new Query(person, this);
  connect(query, SIGNAL(closed()), this, SLOT(queryClosed()));
  m_conversations.append((Conversation *) query);
  return query;
}

Channel *Session::createChannel(const QString &name)
{
  Channel *channel = new Channel(name, this);
  connect(channel, SIGNAL(closed()), this, SLOT(channelClosed()));
  m_conversations.append((Conversation *) channel);
  return channel;
}

void Session::removeConversation(Conversation *conversation)
{
  m_conversations.removeOne(conversation);
  connect(conversation, 0, 0, 0);
  conversation->deleteLater();
}
