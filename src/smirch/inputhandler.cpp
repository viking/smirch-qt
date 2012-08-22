#include "inputhandler.h"
#include "abstracttab.h"
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
    else if (commandName == "echo") {
      emit echoCommandReceived(predicate);
      return;
    }
  }
  else if (!target.isEmpty()) {
    command = IrcCommand::createMessage(target, text);
  }

  if (command == NULL) {
    AbstractTab *tab = qobject_cast<AbstractTab *>(sender());
    if (tab != NULL) {
      tab->appendMessage(QString("Unknown command: %1").arg(text));
    }
  }
  else {
    emit ircCommandReceived(command);
  }
}
