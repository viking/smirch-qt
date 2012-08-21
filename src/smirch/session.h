#ifndef __SESSION_H
#define __SESSION_H

#include <IrcSession>
#include <IrcMessage>
#include <IrcCommand>
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

  signals:
    void queryStarted(Query *query);
    void channelJoined(Channel *channel);
    void serverNumericMessageReceived(IrcNumericMessage *message);
    void serverCapabilityMessageReceived(IrcCapabilityMessage *message);
    void noticeMessageReceived(IrcNoticeMessage *message);

  private slots:
    void handleMessage(IrcMessage *message);
    void handleCommand(IrcCommand *command);

  private:
    QMutex m_mutex;
    QList<Conversation *> m_conversations;

    Query *createQuery(Person *person);
    Channel *createChannel(const QString &name);
};

#endif
