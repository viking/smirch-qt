#include "channel.h"

Channel::Channel(const QString &name, QObject *parent)
  : Conversation(parent), m_name(name)
{
}

const QString &Channel::name() const
{
  return m_name;
}

const QString &Channel::recipient() const
{
  return name();
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
