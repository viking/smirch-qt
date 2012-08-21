#ifndef __MESSAGEFORMATTER_H
#define __MESSAGEFORMATTER_H

#include <QObject>
#include <IrcMessage>

class MessageFormatter : public QObject
{
  Q_OBJECT

  public:
    static QString format(IrcMessage *message, int id);
    static QString format(IrcErrorMessage *message, int id);
    static QString format(IrcInviteMessage *message, int id);
    static QString format(IrcJoinMessage *message, int id);
    static QString format(IrcKickMessage *message, int id);
    static QString format(IrcModeMessage *message, int id);
    static QString format(IrcNickMessage *message, int id);
    static QString format(IrcNoticeMessage *message, int id);
    static QString format(IrcNumericMessage *message, int id);
    static QString format(IrcPartMessage *message, int id);
    static QString format(IrcPingMessage *message, int id);
    static QString format(IrcPongMessage *message, int id);
    static QString format(IrcPrivateMessage *message, int id);
    static QString format(IrcQuitMessage *message, int id);
    static QString format(IrcTopicMessage *message, int id);

    static QString currentTimestamp();

    static const QString s_defaultTemplate;
    static const QString s_messageTemplate;
    static const QString s_actionTemplate;
    static const QString s_joinTemplate;
    static const QString s_numericTemplate;
    static const QString s_partTemplate;
    static const QString s_partWithReasonTemplate;
    static const QString s_quitTemplate;
    static const QString s_quitWithReasonTemplate;
};

#endif
