#ifndef __PERSON_H
#define __PERSON_H

#include <IrcSender>
#include <QString>
#include <QObject>

class Person : public QObject
{
  Q_OBJECT

  public:
    Person(const IrcSender &sender, QObject *parent = 0);

    bool operator==(const Person &person);
    const QString &name() const;
    const QString &user() const;
    const QString &host() const;

  private:
    QString m_name;
    QString m_host;
    QString m_user;
};

#endif
