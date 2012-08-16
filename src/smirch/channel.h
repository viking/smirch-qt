#ifndef __CHANNEL_H
#define __CHANNEL_H

#include <QStringList>
#include "conversation.h"

class Channel : public Conversation
{
  Q_OBJECT

  public:
    Channel(const QString &name, QObject *parent = 0);

    const QString &name() const;
    const QString &recipient() const;
    const QStringList &nicks() const;

    bool includes(IrcJoinMessage *message);
    bool includes(IrcKickMessage *message);
    bool includes(IrcModeMessage *message);
    bool includes(IrcNumericMessage *message);
    bool includes(IrcPartMessage *message);
    bool includes(IrcPrivateMessage *message);
    bool includes(IrcTopicMessage *message);

    void handleNumericMessage(IrcNumericMessage *message);

  signals:
    void nicksChanged(const QStringList &nicks);

  private:
    QString m_name;
    QStringList m_nicks;
    QStringList m_newNicks;
};

#endif
