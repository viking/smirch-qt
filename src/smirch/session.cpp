#include "session.h"

#include <QtDebug>

Session::Session(QObject *parent)
  : IrcSession(parent)
{
  connect(this, SIGNAL(messageReceived(IrcMessage *)),
      this, SLOT(handleMessage(IrcMessage *)));
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

  if (sendCommand(command)) {
    if (message != NULL) {
      handleMessage(message);
    }
  }
  else {
    qDebug() << "Failed to send command:" << command->toString();
  }
}

Query *Session::createQuery(Person *person)
{
  Query *query = new Query(person, this);
  m_conversations.append((Conversation *) query);
  return query;
}

Channel *Session::createChannel(const QString &name)
{
  Channel *channel = new Channel(name, this);
  m_conversations.append((Conversation *) channel);
  return channel;
}
