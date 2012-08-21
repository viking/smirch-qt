#include "query.h"

Query::Query(Person *person, QObject *parent)
  : Conversation(parent), m_person(person)
{
}

QString Query::recipient() const
{
  return m_person->name();
}

Person *Query::person() const
{
  return m_person;
}
