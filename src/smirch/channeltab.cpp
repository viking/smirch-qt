#include "channeltab.h"
#include "channel.h"
#include <QtDebug>

ChannelTab::ChannelTab(Conversation *conversation, QWidget *parent)
  : AbstractTab(conversation, parent)
{
  setupUi();
}

QWebView *ChannelTab::webView() const
{
  return m_ui.webView;
}

QLineEdit *ChannelTab::lineEdit() const
{
  return m_ui.lineEdit;
}

void ChannelTab::setupUi()
{
  m_ui.setupUi(this);
  setupLineEdit();
  m_ui.nicks->setModel(static_cast<Channel *>(m_conversation)->nickListModel());
  setFocusProxy(m_ui.lineEdit);
}
