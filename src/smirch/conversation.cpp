#include "conversation.h"

Conversation::Conversation(QObject *parent)
  : QObject(parent)
{
}

const QString &Conversation::recipient() const
{
  return QString();
}

bool Conversation::includes(IrcMessage *message)
{
  return false;
}

bool Conversation::includes(IrcErrorMessage *message)
{
  return false;
}

bool Conversation::includes(IrcInviteMessage *message)
{
  return false;
}

bool Conversation::includes(IrcJoinMessage *message)
{
  return false;
}

bool Conversation::includes(IrcKickMessage *message)
{
  return false;
}

bool Conversation::includes(IrcModeMessage *message)
{
  return false;
}

bool Conversation::includes(IrcNickMessage *message)
{
  return false;
}

bool Conversation::includes(IrcNoticeMessage *message)
{
  return false;
}

bool Conversation::includes(IrcNumericMessage *message)
{
  return false;
}

bool Conversation::includes(IrcPartMessage *message)
{
  return false;
}

bool Conversation::includes(IrcPingMessage *message)
{
  return false;
}

bool Conversation::includes(IrcPongMessage *message)
{
  return false;
}

bool Conversation::includes(IrcPrivateMessage *message)
{
  return false;
}

bool Conversation::includes(IrcQuitMessage *message)
{
  return false;
}

bool Conversation::includes(IrcTopicMessage *message)
{
  return false;
}

void Conversation::handleUnknownMessage(IrcMessage *message)
{
  emit unknownMessageReceived(message);
}

void Conversation::handleErrorMessage(IrcErrorMessage *message)
{
  emit errorMessageReceived(message);
}

void Conversation::handleInviteMessage(IrcInviteMessage *message)
{
  emit inviteMessageReceived(message);
}

void Conversation::handleJoinMessage(IrcJoinMessage *message)
{
  emit joinMessageReceived(message);
}

void Conversation::handleKickMessage(IrcKickMessage *message)
{
  emit kickMessageReceived(message);
}

void Conversation::handleModeMessage(IrcModeMessage *message)
{
  emit modeMessageReceived(message);
}

void Conversation::handleNickMessage(IrcNickMessage *message)
{
  emit nickMessageReceived(message);
}

void Conversation::handleNoticeMessage(IrcNoticeMessage *message)
{
  emit noticeMessageReceived(message);
}

void Conversation::handleNumericMessage(IrcNumericMessage *message)
{
  emit numericMessageReceived(message);
}

void Conversation::handlePartMessage(IrcPartMessage *message)
{
  emit partMessageReceived(message);
}

void Conversation::handlePingMessage(IrcPingMessage *message)
{
  emit pingMessageReceived(message);
}

void Conversation::handlePongMessage(IrcPongMessage *message)
{
  emit pongMessageReceived(message);
}

void Conversation::handlePrivateMessage(IrcPrivateMessage *message)
{
  emit privateMessageReceived(message);
}

void Conversation::handleQuitMessage(IrcQuitMessage *message)
{
  emit quitMessageReceived(message);
}

void Conversation::handleTopicMessage(IrcTopicMessage *message)
{
  emit topicMessageReceived(message);
}
