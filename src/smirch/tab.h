#ifndef __TAB_H
#define __TAB_H

#include <QWidget>
#include <IrcSession>
#include <IrcMessage>
#include "ui_tab.h"

class Tab : public QWidget
{
  Q_OBJECT

  public:
    enum Type {
      ServerTab,
      ChannelTab,
      QueryTab
    };

    Tab(QWidget *parent = 0);
    Tab(Type type, QWidget *parent = 0);

    IrcSession *session();
    void setSession(IrcSession *session);
    void setName(const QString &name);

  signals:
    void channelJoined(const QString &name);

  private slots:
    void on_lineEdit_returnPressed();
    void sessionDestroyed(QObject *object);

    void connecting();
    void connected();
    void disconnected();
    void messageReceived(IrcMessage *message);

  private:
    Ui::Tab ui;
    Type m_type;
    IrcSession *m_session;
    QString m_name;
};

#endif
