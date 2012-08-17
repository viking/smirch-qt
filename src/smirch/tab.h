#ifndef __TAB_H
#define __TAB_H

#include "abstracttab.h"
#include "ui_tab.h"

class Tab : public AbstractTab
{
  Q_OBJECT

  public:
    Tab(QWidget *parent = 0);
    Tab(Conversation *conversation, QWidget *parent = 0);

  protected:
    QTextEdit *textEdit() const;

  private slots:
    void on_lineEdit_returnPressed();

  private:
    Ui::Tab m_ui;

    void setupUi();
};

#endif
