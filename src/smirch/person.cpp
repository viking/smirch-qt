#include "person.h"

Person::Person(QObject *parent)
  : QObject(parent)
{
}

Person::Person(const IrcSender &sender, QObject *parent)
  : QObject(parent)
{
  m_name = sender.name();
  m_user = sender.user();
  m_host = sender.host();
}

Person::Person(const QString &name, QObject *parent)
  : QObject(parent), m_name(name)
{
}

bool Person::operator==(const Person &person)
{
  return m_name == person.name() && m_user == person.user() &&
    m_host == person.host();
}

const QString &Person::name() const
{
  return m_name;
}

void Person::setName(const QString &name)
{
  m_name = name;
}

const QString &Person::user() const
{
  return m_user;
}

void Person::setUser(const QString &user)
{
  m_user = user;
}

const QString &Person::host() const
{
  return m_host;
}

void Person::setHost(const QString &host)
{
  m_host = host;
}
