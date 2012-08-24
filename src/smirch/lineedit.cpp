#include <QAbstractItemView>
#include <QKeyEvent>
#include <QScrollBar>
#include "lineedit.h"
#include "nicklistmodel.h"

#include <QtDebug>

LineEdit::LineEdit(QWidget *parent)
  : QLineEdit(parent), m_completer(NULL), m_historyPosition(0)
{
}

LineEdit::LineEdit(const QString &contents, QWidget *parent)
  : QLineEdit(contents, parent), m_completer(NULL), m_historyPosition(0)
{
}

LineEdit::~LineEdit()
{
}

void LineEdit::setCompleter(QCompleter *completer)
{
  if (m_completer) {
    QObject::disconnect(m_completer, 0, this, 0);
  }

  m_completer = completer;

  if (!m_completer) {
    return;
  }

  m_completer->setWidget(this);
  m_completer->setCompletionMode(QCompleter::PopupCompletion);
  m_completer->setCaseSensitivity(Qt::CaseInsensitive);
  QObject::connect(m_completer, SIGNAL(activated(QString)),
      this, SLOT(insertCompletion(QString)));
}

QCompleter *LineEdit::completer() const
{
  return m_completer;
}

bool LineEdit::event(QEvent *event)
{
  /* Don't handle non-keyboard events */
  if (event->type() != QEvent::KeyPress) {
    return QLineEdit::event(event);
  }
  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

  /* If there's a completer and it's visible, forward certain keys */
  if (m_completer != NULL && m_completer->popup()->isVisible()) {
    switch (keyEvent->key()) {
      case Qt::Key_Enter:
      case Qt::Key_Return:
      case Qt::Key_Escape:
      case Qt::Key_Tab:
      case Qt::Key_Backtab:
      case Qt::Key_Up:
      case Qt::Key_Down:
        event->ignore(); // let the completer do default behavior
        return true;
      default:
        break;
    }
  }

  switch (keyEvent->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
      // If the return key is pressed, save the input and return
      m_history << text();
      emit returnPressed();
      event->accept();
      return true;

    case Qt::Key_Up:
      rollback();
      event->accept();
      return true;

    case Qt::Key_Down:
      advance();
      event->accept();
      return true;
  }

  if (m_completer == NULL) {
    // There's no completer, so nothing left to do
    return QLineEdit::event(event);
  }

  bool isShortcut = (keyEvent->key() == Qt::Key_Tab);
  if (!isShortcut) {
    // Trigger the default event unless it's the shortcut
    QLineEdit::event(event);
  }

  // If the completer is showing or the user hits the shortcut, update
  // the completer and show it (if hidden).
  if (m_completer->popup()->isVisible() || isShortcut) {
    QString completionPrefix = currentPrefix();
    if (completionPrefix != m_completer->completionPrefix()) {
      m_completer->setCompletionPrefix(completionPrefix);
      m_completer->popup()->setCurrentIndex(m_completer->completionModel()->index(0, 0));
    }

    if (isShortcut) {
      // If there's only one option, go ahead and complete it
      if (m_completer->completionCount() == 1) {
        insertCompletion(m_completer->currentCompletion());
      }
      else {
        QRect cr = cursorRect();
        cr.setWidth(m_completer->popup()->sizeHintForColumn(0)
            + m_completer->popup()->verticalScrollBar()->sizeHint().width());
        m_completer->complete(cr);
      }
    }
  }

  return true;
}

void LineEdit::focusInEvent(QFocusEvent *event)
{
  if (m_completer) {
    m_completer->setWidget(this);
  }
  QLineEdit::focusInEvent(event);
}

void LineEdit::insertCompletion(const QString &completion)
{
  if (m_completer->widget() != this)
    return;

  int extra = completion.length() - m_completer->completionPrefix().length();
  QString result = completion.right(extra);
  if (isCurrentWordAtBeginning()) {
    result.append(':');
  }
  insert(result + QString(" "));
}

// FIXME: save any currently entered text?
void LineEdit::rollback()
{
  if (text().isEmpty()) {
    m_historyPosition = 0;
  }
  int index = m_history.count() + m_historyPosition - 1;
  if (index >= 0) {
    setText(m_history[index]);
    m_historyPosition--;
  }
}

void LineEdit::advance()
{
  if (text().isEmpty()) {
    m_historyPosition = 0;
  }
  int index = m_history.count() + m_historyPosition + 1;
  if (index < m_history.count()) {
    setText(m_history[index]);
    m_historyPosition++;
  }
}

int LineEdit::startIndexOfCurrentWord() const
{
  QString str = text();
  int position = cursorPosition();
  return str.lastIndexOf(QRegExp("\\W"), position) + 1;
}

QString LineEdit::currentPrefix() const
{
  QString str = text();
  int position = cursorPosition();
  int startIndex = startIndexOfCurrentWord();
  return str.mid(startIndex, position - startIndex);
}

bool LineEdit::isCurrentWordAtBeginning() const
{
  return startIndexOfCurrentWord() == 0;
}
