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

  switch (message->type()) {
    case IrcMessage::Unknown:
      {
        conversation = findConversation<IrcMessage *>(message);
        if (conversation != NULL) {
          conversation->handleUnknownMessage(message);
        }
      }
      break;

    case IrcMessage::Error:
      {
        IrcErrorMessage *m = static_cast<IrcErrorMessage *>(message);
        conversation = findConversation<IrcErrorMessage *>(m);
        if (conversation != NULL) {
          conversation->handleErrorMessage(m);
        }
      }
      break;

    case IrcMessage::Invite:
      {
        IrcInviteMessage *m = static_cast<IrcInviteMessage *>(message);
        conversation = findConversation<IrcInviteMessage *>(m);
        if (conversation != NULL) {
          conversation->handleInviteMessage(m);
        }
      }
      break;

    case IrcMessage::Join:
      {
        IrcJoinMessage *m = static_cast<IrcJoinMessage *>(message);

        if (m->isOwn()) {
          Channel *channel = createChannel(m->channel());
          emit channelJoined(channel);
          conversation = (Conversation *) channel;
        }
        else {
          conversation = findConversation<IrcJoinMessage *>(m);
        }

        if (conversation != NULL) {
          conversation->handleJoinMessage(m);
        }
      }
      break;

    case IrcMessage::Kick:
      {
        IrcKickMessage *m = static_cast<IrcKickMessage *>(message);
        conversation = findConversation<IrcKickMessage *>(m);
        if (conversation != NULL) {
          conversation->handleKickMessage(m);
        }
      }
      break;

    case IrcMessage::Mode:
      {
        IrcModeMessage *m = static_cast<IrcModeMessage *>(message);
        conversation = findConversation<IrcModeMessage *>(m);
        if (conversation != NULL) {
          conversation->handleModeMessage(m);
        }
      }
      break;

    case IrcMessage::Nick:
      {
        IrcNickMessage *m = static_cast<IrcNickMessage *>(message);
        conversation = findConversation<IrcNickMessage *>(m);
        if (conversation != NULL) {
          conversation->handleNickMessage(m);
        }
      }
      break;

    case IrcMessage::Notice:
      {
        IrcNoticeMessage *m = static_cast<IrcNoticeMessage *>(message);
        conversation = findConversation<IrcNoticeMessage *>(m);
        if (conversation != NULL) {
          conversation->handleNoticeMessage(m);
        }
      }
      break;

    case IrcMessage::Numeric:
      {
        IrcNumericMessage *m = static_cast<IrcNumericMessage *>(message);
        conversation = findConversation<IrcNumericMessage *>(m);
        if (conversation == NULL) {
          emit serverNumericMessageReceived(m);
        }
        else {
          conversation->handleNumericMessage(m);
        }
      }
      break;

    case IrcMessage::Part:
      {
        IrcPartMessage *m = static_cast<IrcPartMessage *>(message);
        conversation = findConversation<IrcPartMessage *>(m);
        if (conversation != NULL) {
          conversation->handlePartMessage(m);
        }
      }
      break;

    case IrcMessage::Ping:
      {
        IrcPingMessage *m = static_cast<IrcPingMessage *>(message);
        conversation = findConversation<IrcPingMessage *>(m);
        if (conversation != NULL) {
          conversation->handlePingMessage(m);
        }
      }
      break;

    case IrcMessage::Pong:
      {
        IrcPongMessage *m = static_cast<IrcPongMessage *>(message);
        conversation = findConversation<IrcPongMessage *>(m);
        if (conversation != NULL) {
          conversation->handlePongMessage(m);
        }
      }
      break;

    case IrcMessage::Private:
      {
        IrcPrivateMessage *m = static_cast<IrcPrivateMessage *>(message);
        conversation = findConversation<IrcPrivateMessage *>(m);

        if (conversation == NULL) {
          /* FIXME: Always create a new query here? */
          Person *person = new Person(m->sender(), this);
          Query *query = createQuery(person);
          emit queryStarted(query);
          conversation = (Conversation *) query;
        }

        conversation->handlePrivateMessage(m);
      }
      break;

    case IrcMessage::Quit:
      {
        IrcQuitMessage *m = static_cast<IrcQuitMessage *>(message);
        conversation = findConversation<IrcQuitMessage *>(m);
        if (conversation != NULL) {
          conversation->handleQuitMessage(m);
        }
      }
      break;

    case IrcMessage::Topic:
      {
        IrcTopicMessage *m = static_cast<IrcTopicMessage *>(message);
        conversation = findConversation<IrcTopicMessage *>(m);
        if (conversation != NULL) {
          conversation->handleTopicMessage(m);
        }
      }
      break;
  }
}

Query *Session::createQuery(Person *person)
{
  Query *query = new Query(person, this);

  m_mutex.lock();
  m_conversations.append((Conversation *) query);
  m_mutex.unlock();

  return query;
}

Channel *Session::createChannel(const QString &name)
{
  Channel *channel = new Channel(name, this);

  m_mutex.lock();
  m_conversations.append((Conversation *) channel);
  m_mutex.unlock();

  return channel;
}
