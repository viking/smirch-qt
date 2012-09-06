#ifndef __ABSTRACTTAB_H
#define __ABSTRACTTAB_H

#include <QWidget>
#include <QWebFrame>
#include <QWebElement>
#include <QCloseEvent>
#include <QFont>
#include "conversation.h"
#include "lineedit.h"
#include "webview.h"

class AbstractTab : public QWidget
{
  Q_OBJECT

  public:
    AbstractTab(QWidget *parent = 0);
    AbstractTab(Conversation *conversation, QWidget *parent = 0);

    QString recipient() const;
    void appendMessage(QString text);

  signals:
    void inputReceived(const QString &target, const QString &text);

  public slots:
    void setFont(const QFont &font);
    void noticeMessageReceived(IrcNoticeMessage *message);
    void echoReceived(const QString &text);

  protected slots:
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
    void numericMessageReceived(IrcNumericMessage *message);
    void partMessageReceived(IrcPartMessage *message);
    void pingMessageReceived(IrcPingMessage *message);
    void pongMessageReceived(IrcPongMessage *message);
    void privateMessageReceived(IrcPrivateMessage *message);
    void quitMessageReceived(IrcQuitMessage *message);
    void topicMessageReceived(IrcTopicMessage *message);
    void capabilityMessageReceived(IrcCapabilityMessage *message);

  protected:
    Conversation *m_conversation;

    virtual WebView *webView() const = 0;
    virtual LineEdit *lineEdit() const = 0;
    void closeEvent(QCloseEvent *event);

  private:
    int m_messageNumber;
};

#endif
