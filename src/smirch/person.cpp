#include "person.h"

Person::Person(const IrcSender &sender, QObject *parent)
  : QObject(parent)
{
  m_name = sender.name();
  m_user = sender.user();
  m_host = sender.host();
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

const QString &Person::user() const
{
  return m_user;
}

const QString &Person::host() const
{
  return m_host;
}
