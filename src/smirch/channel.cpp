#include <Irc>
#include "channel.h"

Channel::Channel(const QString &name, QObject *parent)
  : Conversation(parent), m_name(name)
{
  m_nickListModel = new NickListModel(this);
}

const QString &Channel::name() const
{
  return m_name;
}

QString Channel::recipient() const
{
  return name();
}

const QStringList &Channel::nicks() const
{
  return m_nickListModel->stringList();
}

NickListModel *Channel::nickListModel() const
{
  return m_nickListModel;
}

bool Channel::includes(IrcJoinMessage *message)
{
  return message->channel() == m_name;
}

bool Channel::includes(IrcKickMessage *message)
{
  return message->channel() == m_name;
}

bool Channel::includes(IrcModeMessage *message)
{
  return message->target() == m_name;
}

bool Channel::includes(IrcNumericMessage *message)
{
  switch (message->code()) {
    case Irc::RPL_NAMREPLY:
      return message->parameters()[2] == m_name;

    case Irc::RPL_ENDOFNAMES:
      return message->parameters()[1] == m_name;

    default:
      return false;
  }
}

bool Channel::includes(IrcPartMessage *message)
{
  return message->channel() == m_name;
}

bool Channel::includes(IrcPrivateMessage *message)
{
  return message->target() == m_name;
}

bool Channel::includes(IrcTopicMessage *message)
{
  return message->channel() == m_name;
}

void Channel::handleNumericMessage(IrcNumericMessage *message)
{
  switch (message->code()) {
    case Irc::RPL_NAMREPLY:
      m_mutex.lock();
      m_newNicks << message->parameters()[3].split(" ");
      m_mutex.unlock();
      break;

    case Irc::RPL_ENDOFNAMES:
      m_mutex.lock();
      m_newNicks.sort();
      m_nickListModel->setStringList(m_newNicks);
      m_newNicks.clear();
      m_mutex.unlock();
      break;

    default:
      emit numericMessageReceived(message);
      break;
  }
}

void Channel::handleJoinMessage(IrcJoinMessage *message)
{
  m_mutex.lock();
  m_nickListModel->addNick(message->sender().name());
  m_mutex.unlock();

  emit joinMessageReceived(message);
}

void Channel::handlePartMessage(IrcPartMessage *message)
{
  m_mutex.lock();
  m_nickListModel->removeNick(message->sender().name());
  m_mutex.unlock();

  emit partMessageReceived(message);
}
