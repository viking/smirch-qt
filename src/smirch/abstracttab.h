#ifndef __ABSTRACTTAB_H
#define __ABSTRACTTAB_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include "conversation.h"

class AbstractTab : public QWidget
{
  Q_OBJECT

  public:
    AbstractTab(QWidget *parent = 0);
    AbstractTab(Conversation *conversation, QWidget *parent = 0);

    QString recipient() const;

  signals:
    void textEntered(const QString &text);

  protected slots:
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

    void handleInput();

  protected:
    Conversation *m_conversation;

    void appendText(QString text);
    virtual QTextEdit *textEdit() const = 0;
    virtual QLineEdit *lineEdit() const = 0;
};

#endif
