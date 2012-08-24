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

LineEdit *ChannelTab::lineEdit() const
{
  return m_ui.lineEdit;
}

void ChannelTab::setupUi()
{
  m_ui.setupUi(this);
  setFocusProxy(m_ui.lineEdit);

  NickListModel *nickListModel = static_cast<Channel *>(m_conversation)->nickListModel();
  m_ui.nicks->setModel(nickListModel);

  m_completer = new QCompleter(nickListModel, this);
  m_ui.lineEdit->setCompleter(m_completer);
}
