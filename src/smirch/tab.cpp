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

void Tab::on_lineEdit_returnPressed()
{
  QString text = m_ui.lineEdit->text();
  emit textEntered(text);
  m_ui.lineEdit->clear();
}

void Tab::setupUi()
{
  m_ui.setupUi(this);
}
