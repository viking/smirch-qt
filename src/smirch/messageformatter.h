#ifndef __MESSAGEFORMATTER_H
#define __MESSAGEFORMATTER_H

#include <QObject>
#include <IrcMessage>

class MessageFormatter : public QObject
{
  Q_OBJECT

  public:
    static QString format(IrcMessage *message);
    static QString format(IrcErrorMessage *message);
    static QString format(IrcInviteMessage *message);
    static QString format(IrcJoinMessage *message);
    static QString format(IrcKickMessage *message);
    static QString format(IrcModeMessage *message);
    static QString format(IrcNickMessage *message);
    static QString format(IrcNoticeMessage *message);
    static QString format(IrcNumericMessage *message);
    static QString format(IrcPartMessage *message);
    static QString format(IrcPingMessage *message);
    static QString format(IrcPongMessage *message);
    static QString format(IrcPrivateMessage *message);
    static QString format(IrcQuitMessage *message);
    static QString format(IrcTopicMessage *message);
};

#endif
