#include <IrcUtil>
#include <QDateTime>
#include "messageformatter.h"

const QString MessageFormatter::s_defaultTemplate =
  QString("<div id=\"message-%1\"><span class=\"timestamp\">[%2]</span> %3</div>\n");
const QString MessageFormatter::s_messageTemplate =
  QString("<div id=\"message-%1\" class=\"message\"><span class=\"timestamp\">[%2]</span> <%3> %4</div>\n");
const QString MessageFormatter::s_actionTemplate =
  QString("<div id=\"message-%1\" class=\"action\"><span class=\"timestamp\">[%2]</span> * %3 %4</div>\n");
const QString MessageFormatter::s_joinTemplate =
  QString("<div id=\"message-%1\" class=\"join\"><span class=\"timestamp\">[%2]</span> * %3 (%4@%5) has joined %6</div>\n");
const QString MessageFormatter::s_numericTemplate =
  QString("<div id=\"message-%1\" class=\"numeric\"><span class=\"timestamp\">[%2]</span> (%3) %4</div>\n");
const QString MessageFormatter::s_partTemplate =
  QString("<div id=\"message-%1\" class=\"part\"><span class=\"timestamp\">[%2]</span> * %3 (%4@%5) has left %6</div>\n");
const QString MessageFormatter::s_partWithReasonTemplate =
  QString("<div id=\"message-%1\" class=\"part\"><span class=\"timestamp\">[%2]</span> * %3 (%4@%5) has left %6 (%7)</div>\n");
const QString MessageFormatter::s_quitTemplate =
  QString("<div id=\"message-%1\" class=\"quit\"><span class=\"timestamp\">[%2]</span> * %3 has quit</div>\n");
const QString MessageFormatter::s_quitWithReasonTemplate =
  QString("<div id=\"message-%1\" class=\"quit\"><span class=\"timestamp\">[%2]</span> * %3 has quit (%4)</div>\n");

QString MessageFormatter::format(IrcMessage *message, int id)
{
  QByteArray data = message->toData();
  return(s_defaultTemplate.arg(id).arg(currentTimestamp()).arg(QString(data)));
}

QString MessageFormatter::format(IrcErrorMessage *message, int id)
{
  return(format((IrcMessage *) message, id));
}

QString MessageFormatter::format(IrcInviteMessage *message, int id)
{
  return(format((IrcMessage *) message, id));
}

QString MessageFormatter::format(IrcJoinMessage *message, int id)
{
  IrcSender s = message->sender();
  return(s_joinTemplate.arg(id).arg(currentTimestamp()).
      arg(s.name()).arg(s.user()).arg(s.host()).arg(message->channel()));
}

QString MessageFormatter::format(IrcKickMessage *message, int id)
{
  return(format((IrcMessage *) message, id));
}

QString MessageFormatter::format(IrcModeMessage *message, int id)
{
  return(format((IrcMessage *) message, id));
}

QString MessageFormatter::format(IrcNickMessage *message, int id)
{
  return(format((IrcMessage *) message, id));
}

QString MessageFormatter::format(IrcNoticeMessage *message, int id)
{
  return(format((IrcMessage *) message, id));
}

QString MessageFormatter::format(IrcNumericMessage *message, int id)
{
  QStringList parameters = message->parameters();
  parameters.removeFirst();
  return(s_numericTemplate.arg(id).arg(currentTimestamp()).
      arg(message->code()).arg(parameters.join(" ")));
}

QString MessageFormatter::format(IrcPartMessage *message, int id)
{
  IrcSender s = message->sender();
  QString str = QString("* %1 (%2@%3) has left %4").
      arg(s.name()).arg(s.user()).arg(s.host()).arg(message->channel());

  if (message->reason().isEmpty()) {
    return(s_partTemplate.arg(id).arg(currentTimestamp()).
        arg(s.name()).arg(s.user()).arg(s.host()).arg(message->channel()));
  }
  else {
    return(s_partWithReasonTemplate.arg(id).arg(currentTimestamp()).
        arg(s.name()).arg(s.user()).arg(s.host()).arg(message->channel()).
        arg(message->reason()));;
  }
}

QString MessageFormatter::format(IrcPingMessage *message, int id)
{
  return(format((IrcMessage *) message, id));
}

QString MessageFormatter::format(IrcPongMessage *message, int id)
{
  return(format((IrcMessage *) message, id));
}

QString MessageFormatter::format(IrcPrivateMessage *message, int id)
{
  if (message->isAction()) {
    return(s_actionTemplate.arg(id).arg(currentTimestamp()).
        arg(message->sender().name()).
        arg(IrcUtil::messageToHtml(message->message())));
  }
  else {
    return(s_messageTemplate.arg(id).arg(currentTimestamp()).
        arg(message->sender().name()).
        arg(IrcUtil::messageToHtml(message->message())));
  }
}

QString MessageFormatter::format(IrcQuitMessage *message, int id)
{
  if (message->reason().isEmpty()) {
    return(s_quitTemplate.arg(id).arg(currentTimestamp()).
        arg(message->sender().name()));
  }
  else {
    return(s_quitWithReasonTemplate.arg(id).arg(currentTimestamp()).
        arg(message->sender().name()).arg(message->reason()));
  }
}

QString MessageFormatter::format(IrcTopicMessage *message, int id)
{
  return(format((IrcMessage *) message, id));
}

QString MessageFormatter::currentTimestamp()
{
  return QDateTime::currentDateTime().toString("hh:mm");
}
