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

void Tab::appendText(QString text)
{
  m_ui.textBrowser->append(text);
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
