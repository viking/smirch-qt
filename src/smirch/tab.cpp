#include "tab.h"

Tab::Tab(QWidget *parent)
  : AbstractTab(parent)
{
  setupUi();
}

Tab::Tab(Conversation *conversation, QWidget *parent)
  : AbstractTab(conversation, parent)
{
  setupUi();
}

QTextEdit *Tab::textEdit() const
{
  return m_ui.textEdit;
}

QLineEdit *Tab::lineEdit() const
{
  return m_ui.lineEdit;
}

void Tab::setupUi()
{
  m_ui.setupUi(this);
  connect(m_ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(handleInput()));
}
