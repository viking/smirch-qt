#ifndef __SESSION_H
#define __SESSION_H

#include <IrcSession>
#include <IrcMessage>
#include <IrcCommand>
#include <QSslSocket>
#include <QMutex>
#include <QList>

#include "conversation.h"
#include "query.h"
#include "channel.h"

class Session : public IrcSession
{
  Q_OBJECT

  public:
    Session(QObject *parent = 0);
    void setNickPassword(const QString &nickPassword);
    void useSsl();

  signals:
    void queryStarted(Query *query);
    void channelJoined(Channel *channel);
    void serverNumericMessageReceived(IrcNumericMessage *message);
    void serverCapabilityMessageReceived(IrcCapabilityMessage *message);
    void noticeMessageReceived(IrcNoticeMessage *message);

  private slots:
    void sendPassword(QString *password);
    void handleMessage(IrcMessage *message);
    void handleCommand(IrcCommand *command);
    void channelClosed();
    void queryClosed();
    void sslErrorsOccurred(const QList<QSslError> &errors);

  private:
    QMutex m_mutex;
    QList<Conversation *> m_conversations;
    QString m_nickPassword;

    Query *createQuery(Person *person);
    Channel *createChannel(const QString &name);
    void removeConversation(Conversation *conversation);
};

#endif
