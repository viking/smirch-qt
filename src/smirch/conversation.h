#ifndef __CONVERSATION_H
#define __CONVERSATION_H

#include <IrcMessage>
#include <QObject>

class Conversation : public QObject
{
  Q_OBJECT

  public:
    Conversation(QObject *parent = 0);

    virtual QString recipient() const;

    virtual bool includes(IrcMessage *message);
    virtual bool includes(IrcErrorMessage *message);
    virtual bool includes(IrcInviteMessage *message);
    virtual bool includes(IrcJoinMessage *message);
    virtual bool includes(IrcKickMessage *message);
    virtual bool includes(IrcModeMessage *message);
    virtual bool includes(IrcNickMessage *message);
    virtual bool includes(IrcNoticeMessage *message);
    virtual bool includes(IrcNumericMessage *message);
    virtual bool includes(IrcPartMessage *message);
    virtual bool includes(IrcPingMessage *message);
    virtual bool includes(IrcPongMessage *message);
    virtual bool includes(IrcPrivateMessage *message);
    virtual bool includes(IrcQuitMessage *message);
    virtual bool includes(IrcTopicMessage *message);
    virtual bool includes(IrcCapabilityMessage *message);

    virtual void handleMessage(IrcMessage *message);
    virtual void handleUnknownMessage(IrcMessage *message);
    virtual void handleErrorMessage(IrcErrorMessage *message);
    virtual void handleInviteMessage(IrcInviteMessage *message);
    virtual void handleJoinMessage(IrcJoinMessage *message);
    virtual void handleKickMessage(IrcKickMessage *message);
    virtual void handleModeMessage(IrcModeMessage *message);
    virtual void handleNickMessage(IrcNickMessage *message);
    virtual void handleNoticeMessage(IrcNoticeMessage *message);
    virtual void handleNumericMessage(IrcNumericMessage *message);
    virtual void handlePartMessage(IrcPartMessage *message);
    virtual void handlePingMessage(IrcPingMessage *message);
    virtual void handlePongMessage(IrcPongMessage *message);
    virtual void handlePrivateMessage(IrcPrivateMessage *message);
    virtual void handleQuitMessage(IrcQuitMessage *message);
    virtual void handleTopicMessage(IrcTopicMessage *message);
    virtual void handleCapabilityMessage(IrcCapabilityMessage *message);

  signals:
    void unknownMessageReceived(IrcMessage *message);
    void errorMessageReceived(IrcErrorMessage *message);
    void inviteMessageReceived(IrcInviteMessage *message);
    void joinMessageReceived(IrcJoinMessage *message);
    void kickMessageReceived(IrcKickMessage *message);
    void modeMessageReceived(IrcModeMessage *message);
    void nickMessageReceived(IrcNickMessage *message);
    void noticeMessageReceived(IrcNoticeMessage *message);
    void numericMessageReceived(IrcNumericMessage *message);
    void partMessageReceived(IrcPartMessage *message);
    void pingMessageReceived(IrcPingMessage *message);
    void pongMessageReceived(IrcPongMessage *message);
    void privateMessageReceived(IrcPrivateMessage *message);
    void quitMessageReceived(IrcQuitMessage *message);
    void topicMessageReceived(IrcTopicMessage *message);
    void capabilityMessageReceived(IrcCapabilityMessage *message);
    void closed();

  public slots:
    virtual void close();
};

#endif
