#include "inputhandler.h"
#include "abstracttab.h"
#include <QtDebug>

const QRegExp InputHandler::s_spacesPattern = QRegExp("\\s+");

InputHandler::InputHandler(QObject *parent)
  : QObject(parent)
{
}

void InputHandler::handleInput(const QString &target, const QString &text)
{
  IrcCommand *command = NULL;
  if (text.startsWith("/")) {
    QString commandName = text.section(s_spacesPattern, 0, 0).mid(1).toLower();
    QString predicate = text.section(s_spacesPattern, 1);
    QStringList args = predicate.split(s_spacesPattern);

    if (commandName == "join") {
      if (args.count() > 0) {
        command = IrcCommand::createJoin(args[0]);
      }
    }
    else if (commandName == "msg") {
      if (args.count() > 1) {
        command = IrcCommand::createMessage(args[0], predicate.section(" ", 1));
      }
    }
    else if (commandName == "names") {
      if (args.count() > 0) {
        command = IrcCommand::createNames(args[0]);
      }
    }
    else if (commandName == "notice") {
      if (args.count() > 1) {
        command = IrcCommand::createNotice(args[0], predicate.section(" ", 1));
      }
    }
    else if (commandName == "part") {
      if (args.count() > 0) {
        command = IrcCommand::createPart(args[0]);
      }
    }
    else if (commandName == "quit") {
      command = IrcCommand::createQuit(predicate);
    }
    else if (commandName == "topic") {
      if (args.count() > 0) {
        if (args[0].startsWith('#')) {
          command = IrcCommand::createTopic(args[0], predicate.section(" ", 1));
        }
        else {
          command = IrcCommand::createTopic(target, predicate);
        }
      }
    }
    else if (commandName == "who") {
      if (args.count() > 0) {
        command = IrcCommand::createWho(args[0]);
      }
    }
    else if (commandName == "whois") {
      if (args.count() > 0) {
        command = IrcCommand::createWhois(args[0]);
      }
    }
    else if (commandName == "whowas") {
      if (args.count() > 0) {
        command = IrcCommand::createWhowas(args[0]);
      }
    }
    else if (commandName == "echo") {
      emit echoCommandReceived(predicate);
      return;
    }
    else if (commandName == "close") {
      emit closeCommandReceived();
      return;
    }
  }
  else if (!target.isEmpty()) {
    command = IrcCommand::createMessage(target, text);
  }

  if (command == NULL) {
    AbstractTab *tab = qobject_cast<AbstractTab *>(sender());
    if (tab != NULL) {
      tab->echoReceived(QString("Unknown command: %1").arg(text));
    }
  }
  else {
    emit ircCommandReceived(command);
  }
}
