#ifndef __INPUTHANDLER_H
#define __INPUTHANDLER_H

#include <QObject>
#include <IrcCommand>

class InputHandler : public QObject
{
  Q_OBJECT

  public:
    InputHandler(QObject *parent = 0);

  signals:
    void commandReady(IrcCommand *command);

  public slots:
    void handleInput(const QString &target, const QString &text);
};

#endif
