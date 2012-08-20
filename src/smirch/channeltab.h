#ifndef __CHANNELTAB_H
#define __CHANNELTAB_H

#include "abstracttab.h"
#include "ui_channeltab.h"

class ChannelTab : public AbstractTab
{
  Q_OBJECT

  public:
    ChannelTab(Conversation *conversation, QWidget *parent = 0);

  protected:
    QTextEdit *textEdit() const;
    QLineEdit *lineEdit() const;

  private:
    Ui::ChannelTab m_ui;

    void setupUi();
};

#endif
