#ifndef __QUERY_H
#define __QUERY_H

#include "conversation.h"
#include "person.h"

class Query : public Conversation
{
  Q_OBJECT

  public:
    Query(Person *person, QObject *parent = 0);

    Person *person() const;
    QString recipient() const;

  private:
    Person *m_person;
};

#endif
