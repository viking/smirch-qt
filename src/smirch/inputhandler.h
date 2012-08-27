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
    void ircCommandReceived(IrcCommand *command);
    void echoCommandReceived(const QString &text);
    void closeCommandReceived();

  public slots:
    void handleInput(const QString &target, const QString &text);

  private:
    static const QRegExp s_spacesPattern;
};

#endif
