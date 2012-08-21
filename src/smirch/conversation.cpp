#include "conversation.h"

Conversation::Conversation(QObject *parent)
  : QObject(parent)
{
}

QString Conversation::recipient() const
{
  return QString();
}

bool Conversation::includes(IrcMessage *message)
{
  switch (message->type()) {
    case IrcMessage::Unknown:
      return false;

    case IrcMessage::Error:
      return includes(static_cast<IrcErrorMessage *>(message));

    case IrcMessage::Invite:
      return includes(static_cast<IrcInviteMessage *>(message));

    case IrcMessage::Join:
      return includes(static_cast<IrcJoinMessage *>(message));

    case IrcMessage::Kick:
      return includes(static_cast<IrcKickMessage *>(message));

    case IrcMessage::Mode:
      return includes(static_cast<IrcModeMessage *>(message));

    case IrcMessage::Nick:
      return includes(static_cast<IrcNickMessage *>(message));

    case IrcMessage::Notice:
      return includes(static_cast<IrcNoticeMessage *>(message));

    case IrcMessage::Numeric:
      return includes(static_cast<IrcNumericMessage *>(message));

    case IrcMessage::Part:
      return includes(static_cast<IrcPartMessage *>(message));

    case IrcMessage::Ping:
      return includes(static_cast<IrcPingMessage *>(message));

    case IrcMessage::Pong:
      return includes(static_cast<IrcPongMessage *>(message));

    case IrcMessage::Private:
      return includes(static_cast<IrcPrivateMessage *>(message));

    case IrcMessage::Quit:
      return includes(static_cast<IrcQuitMessage *>(message));

    case IrcMessage::Topic:
      return includes(static_cast<IrcTopicMessage *>(message));
  }

  return false;
}

bool Conversation::includes(IrcErrorMessage *)
{
  return false;
}

bool Conversation::includes(IrcInviteMessage *)
{
  return false;
}

bool Conversation::includes(IrcJoinMessage *)
{
  return false;
}

bool Conversation::includes(IrcKickMessage *)
{
  return false;
}

bool Conversation::includes(IrcModeMessage *)
{
  return false;
}

bool Conversation::includes(IrcNickMessage *)
{
  return false;
}

bool Conversation::includes(IrcNoticeMessage *)
{
  return false;
}

bool Conversation::includes(IrcNumericMessage *)
{
  return false;
}

bool Conversation::includes(IrcPartMessage *)
{
  return false;
}

bool Conversation::includes(IrcPingMessage *)
{
  return false;
}

bool Conversation::includes(IrcPongMessage *)
{
  return false;
}

bool Conversation::includes(IrcPrivateMessage *)
{
  return false;
}

bool Conversation::includes(IrcQuitMessage *)
{
  return false;
}

bool Conversation::includes(IrcTopicMessage *)
{
  return false;
}

void Conversation::handleMessage(IrcMessage *message)
{
  switch (message->type()) {
    case IrcMessage::Unknown:
      handleUnknownMessage(message);
      break;

    case IrcMessage::Error:
      handleErrorMessage(static_cast<IrcErrorMessage *>(message));
      break;

    case IrcMessage::Invite:
      handleInviteMessage(static_cast<IrcInviteMessage *>(message));
      break;

    case IrcMessage::Join:
      handleJoinMessage(static_cast<IrcJoinMessage *>(message));
      break;

    case IrcMessage::Kick:
      handleKickMessage(static_cast<IrcKickMessage *>(message));
      break;

    case IrcMessage::Mode:
      handleModeMessage(static_cast<IrcModeMessage *>(message));
      break;

    case IrcMessage::Nick:
      handleNickMessage(static_cast<IrcNickMessage *>(message));
      break;

    case IrcMessage::Notice:
      handleNoticeMessage(static_cast<IrcNoticeMessage *>(message));
      break;

    case IrcMessage::Numeric:
      handleNumericMessage(static_cast<IrcNumericMessage *>(message));
      break;

    case IrcMessage::Part:
      handlePartMessage(static_cast<IrcPartMessage *>(message));
      break;

    case IrcMessage::Ping:
      handlePingMessage(static_cast<IrcPingMessage *>(message));
      break;

    case IrcMessage::Pong:
      handlePongMessage(static_cast<IrcPongMessage *>(message));
      break;

    case IrcMessage::Private:
      handlePrivateMessage(static_cast<IrcPrivateMessage *>(message));
      break;

    case IrcMessage::Quit:
      handleQuitMessage(static_cast<IrcQuitMessage *>(message));
      break;

    case IrcMessage::Topic:
      handleTopicMessage(static_cast<IrcTopicMessage *>(message));
      break;
  }
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
