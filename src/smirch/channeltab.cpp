#include "channeltab.h"
#include "channel.h"
#include <QtDebug>

ChannelTab::ChannelTab(Conversation *conversation, QWidget *parent)
  : AbstractTab(conversation, parent)
{
  setupUi();
}

QTextEdit *ChannelTab::textEdit() const
{
  return m_ui.textEdit;
}

void ChannelTab::on_lineEdit_returnPressed()
{
  QString text = m_ui.lineEdit->text();
  emit textEntered(text);
  m_ui.lineEdit->clear();
}

void ChannelTab::setupUi()
{
  m_ui.setupUi(this);
  m_ui.nicks->setModel(static_cast<Channel *>(m_conversation)->nickListModel());
}
