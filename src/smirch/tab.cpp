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

WebView *Tab::webView() const
{
  return m_ui.webView;
}

LineEdit *Tab::lineEdit() const
{
  return m_ui.lineEdit;
}

void Tab::setupUi()
{
  m_ui.setupUi(this);
  setFocusProxy(m_ui.lineEdit);
}
