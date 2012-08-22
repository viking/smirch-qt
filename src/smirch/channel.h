#ifndef __CHANNEL_H
#define __CHANNEL_H

#include <QMutex>
#include <QStringList>
#include "conversation.h"
#include "nicklistmodel.h"

class Channel : public Conversation
{
  Q_OBJECT

  public:
    Channel(const QString &name, QObject *parent = 0);

    const QString &name() const;
    QString recipient() const;
    const QStringList &nicks() const;
    NickListModel *nickListModel() const;

    bool includes(IrcJoinMessage *message);
    bool includes(IrcKickMessage *message);
    bool includes(IrcModeMessage *message);
    bool includes(IrcNumericMessage *message);
    bool includes(IrcPartMessage *message);
    bool includes(IrcQuitMessage *message);
    bool includes(IrcTopicMessage *message);

    void handleNumericMessage(IrcNumericMessage *message);
    void handleJoinMessage(IrcJoinMessage *message);
    void handlePartMessage(IrcPartMessage *message);
    void handleQuitMessage(IrcQuitMessage *message);

  private:
    QString m_name;
    NickListModel *m_nickListModel;
    QStringList m_newNicks;
    QMutex m_mutex;
};

#endif
