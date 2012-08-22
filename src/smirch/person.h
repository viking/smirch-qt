#ifndef __PERSON_H
#define __PERSON_H

#include <IrcSender>
#include <QString>
#include <QObject>

class Person : public QObject
{
  Q_OBJECT

  public:
    Person(QObject *parent = 0);
    Person(const IrcSender &sender, QObject *parent = 0);
    Person(const QString &name, QObject *parent = 0);

    bool operator==(const Person &person);

    const QString &name() const;
    void setName(const QString &name);

    const QString &user() const;
    void setUser(const QString &user);

    const QString &host() const;
    void setHost(const QString &host);

  private:
    QString m_name;
    QString m_host;
    QString m_user;
};

#endif
