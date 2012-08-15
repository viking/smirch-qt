#ifndef __CHANNEL_H
#define __CHANNEL_H

#include <QList>
#include "conversation.h"
#include "person.h"

class Channel : public Conversation
{
  Q_OBJECT

  public:
    Channel(const QString &name, QObject *parent = 0);

    const QString &name() const;
    const QString &recipient() const;

    bool includes(IrcJoinMessage *message);
    bool includes(IrcKickMessage *message);
    bool includes(IrcModeMessage *message);
    bool includes(IrcPartMessage *message);
    bool includes(IrcPrivateMessage *message);
    bool includes(IrcTopicMessage *message);

  private:
    QString m_name;
    QList<Person *> m_people;
};

#endif
