#ifndef __LINEEDIT_H
#define __LINEEDIT_H

#include <QLineEdit>
#include <QCompleter>
#include <QStringList>
#include <QEvent>

class LineEdit : public QLineEdit
{
  Q_OBJECT

  public:
    LineEdit(QWidget *parent = 0);
    LineEdit(const QString &contents, QWidget *parent = 0);
    ~LineEdit();

    void setCompleter(QCompleter *completer);
    QCompleter *completer() const;

  protected:
    bool event(QEvent *event);
    void focusInEvent(QFocusEvent *event);

  private slots:
    void insertCompletion(const QString &completion);

  private:
    QCompleter *m_completer;
    QStringList m_history;
    int m_historyPosition;

    int startIndexOfCurrentWord() const;
    QString currentPrefix() const;
    bool isCurrentWordAtBeginning() const;

    /* History */
    void rollback();
    void advance();
};

#endif
