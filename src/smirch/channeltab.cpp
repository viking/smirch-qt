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

QLineEdit *ChannelTab::lineEdit() const
{
  return m_ui.lineEdit;
}

void ChannelTab::setupUi()
{
  m_ui.setupUi(this);
  m_ui.nicks->setModel(static_cast<Channel *>(m_conversation)->nickListModel());
  connect(m_ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(handleInput()));
}
