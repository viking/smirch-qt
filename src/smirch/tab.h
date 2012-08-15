#ifndef __TAB_H
#define __TAB_H

#include <QWidget>
#include "ui_tab.h"
#include "conversation.h"

class Tab : public QWidget
{
  Q_OBJECT

  public:
    Tab(QWidget *parent = 0);
    Tab(Conversation *conversation, QWidget *parent = 0);

    const QString &recipient();

  signals:
    void textEntered(const QString &text);

  private slots:
    void on_lineEdit_returnPressed();

    void connecting();
    void connected();
    void disconnected();

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

  private:
    Ui::Tab m_ui;
    Conversation *m_conversation;
};

#endif
