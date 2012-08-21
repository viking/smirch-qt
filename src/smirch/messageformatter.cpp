#include <IrcUtil>
#include "messageformatter.h"

QString MessageFormatter::format(IrcMessage *message)
{
  QByteArray data = message->toData();
  return(QString(data));
}

QString MessageFormatter::format(IrcErrorMessage *message)
{
  QByteArray data = message->toData();
  return(QString(data));
}

QString MessageFormatter::format(IrcInviteMessage *message)
{
  QByteArray data = message->toData();
  return(QString(data));
}

QString MessageFormatter::format(IrcJoinMessage *message)
{
  IrcSender s = message->sender();
  return(QString("* %1 (%2@%3) has joined %4").
      arg(s.name()).arg(s.user()).arg(s.host()).arg(message->channel()));
}

QString MessageFormatter::format(IrcKickMessage *message)
{
  QByteArray data = message->toData();
  return(QString(data));
}

QString MessageFormatter::format(IrcModeMessage *message)
{
  QByteArray data = message->toData();
  return(QString(data));
}

QString MessageFormatter::format(IrcNickMessage *message)
{
  QByteArray data = message->toData();
  return(QString(data));
}

QString MessageFormatter::format(IrcNoticeMessage *message)
{
  QByteArray data = message->toData();
  return(QString(data));
}

QString MessageFormatter::format(IrcNumericMessage *message)
{
  QStringList parameters = message->parameters();
  parameters.removeFirst();
  return(QString("(%1) %2").arg(message->code()).
      arg(parameters.join(" ")));
}

QString MessageFormatter::format(IrcPartMessage *message)
{
  IrcSender s = message->sender();
  QString str = QString("* %1 (%2@%3) has left %4").
      arg(s.name()).arg(s.user()).arg(s.host()).arg(message->channel());

  if (!message->reason().isEmpty()) {
    str.append(QString(" (%1)").arg(message->reason()));
  }

  return(str);
}

QString MessageFormatter::format(IrcPingMessage *message)
{
  QByteArray data = message->toData();
  return(QString(data));
}

QString MessageFormatter::format(IrcPongMessage *message)
{
  QByteArray data = message->toData();
  return(QString(data));
}

QString MessageFormatter::format(IrcPrivateMessage *message)
{
  if (message->isAction()) {
    return(QString("* %1 %2").arg(message->sender().name()).
        arg(IrcUtil::messageToHtml(message->message())));
  }
  else {
    return(QString("<%1> %2").arg(message->sender().name()).
        arg(IrcUtil::messageToHtml(message->message())));
  }
}

QString MessageFormatter::format(IrcQuitMessage *message)
{
  if (!message->reason().isEmpty()) {
    return(QString("* %1 has quit (%2)").arg(message->sender().name()).
        arg(message->reason()));
  }
  else {
    return(QString("* %1 has quit").arg(message->sender().name()));
  }
}

QString MessageFormatter::format(IrcTopicMessage *message)
{
  QByteArray data = message->toData();
  return(QString(data));
}
