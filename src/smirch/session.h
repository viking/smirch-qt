#ifndef __SESSION_H
#define __SESSION_H

#include <IrcSession>
#include <IrcMessage>
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

  private slots:
    void handleMessage(IrcMessage *message);

  private:
    QMutex m_mutex;
    QList<Conversation *> m_conversations;

    Query *createQuery(Person *person);
    Channel *createChannel(const QString &name);

    template <class T>
    Conversation *findConversation(T message)
    {
      Conversation *result = NULL;

      m_mutex.lock();
      for (int i = 0; i < m_conversations.size(); i++) {
        Conversation *c = m_conversations[i];
        if (c->includes(message)) {
          result = c;
          break;
        }
      }
      m_mutex.unlock();

      return result;
    }
};

#endif
