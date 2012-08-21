#ifndef __MESSAGEFORMATTER_H
#define __MESSAGEFORMATTER_H

#include <QObject>
#include <IrcMessage>

class MessageFormatter : public QObject
{
  Q_OBJECT

  public:
    static QString formatConnecting(int id, const QString &host);
    static QString formatConnected(int id, const QString &host);
    static QString formatDisconnected(int id);

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
    static QString format(IrcCapabilityMessage *message, int id);

    static QString currentTimestamp();

    static const QString s_connectingTemplate;
    static const QString s_connectedTemplate;
    static const QString s_disconnectedTemplate;
    static const QString s_defaultTemplate;
    static const QString s_joinTemplate;
    static const QString s_numericTemplate;
    static const QString s_partTemplate;
    static const QString s_partWithReasonTemplate;
    static const QString s_privateTemplate;
    static const QString s_actionTemplate;
    static const QString s_quitTemplate;
    static const QString s_quitWithReasonTemplate;
    static const QString s_capabilityTemplate;
};

#endif
