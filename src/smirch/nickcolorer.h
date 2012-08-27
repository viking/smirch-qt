#ifndef __NICKCOLORER_H
#define __NICKCOLORER_H

#include <QObject>
#include <QColor>
#include <QSettings>
#include <IrcSender>

#define GOLDEN_RATIO_CONJ 0.618033988749895

class NickColorer : public QObject
{
  Q_OBJECT

  public:
    static QColor colorFor(const IrcSender &sender);
};

#endif
