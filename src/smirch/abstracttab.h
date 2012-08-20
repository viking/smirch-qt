#ifndef __ABSTRACTTAB_H
#define __ABSTRACTTAB_H

#include <QWidget>
#include <QWebView>
#include <QWebFrame>
#include <QWebElement>
#include <QLineEdit>
#include <QStringList>
#include <QMutex>
#include "conversation.h"

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

  protected slots:
    void on_webView_loadFinished(bool ok);

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
    QWebElement m_body;
    bool m_pageLoaded;

    virtual QWebView *webView() const = 0;
    virtual QLineEdit *lineEdit() const = 0;

  private:
    static const QString s_messageMarkup;
    int m_messageNumber;
    QStringList m_appendQueue;
    QMutex m_appendMutex;

    void internalAppendMessage(const QString &text);
};

#endif
