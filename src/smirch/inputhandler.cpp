#include "inputhandler.h"
#include <QtDebug>

InputHandler::InputHandler(QObject *parent)
  : QObject(parent)
{
}

void InputHandler::handleInput(const QString &target, const QString &text)
{
  IrcCommand *command = NULL;
  if (text.startsWith("/")) {
    QString commandName = text.section(" ", 0, 0).mid(1).toLower();
    QString predicate = text.section(" ", 1);
    if (commandName == "join") {
      QStringList args = predicate.split(" ");
      command = IrcCommand::createJoin(args[0]);
    }
    else if (commandName == "quit") {
      command = IrcCommand::createQuit(predicate);
    }
  }
  else if (!target.isEmpty()) {
    command = IrcCommand::createMessage(target, text);
  }

  if (command == NULL) {
    qDebug() << "Unknown command:" << text;
  }
  else {
    emit commandReady(command);
  }
}
