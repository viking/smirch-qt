#include "channeltab.h"
#include "channel.h"
#include <IrcUtil>
#include <QtDebug>

ChannelTab::ChannelTab(Conversation *conversation, QWidget *parent)
  : AbstractTab(conversation, parent)
{
  setupUi();
  m_ui.topic->hide();
  connect(conversation, SIGNAL(topicChanged(const QString &)),
      this, SLOT(topicChanged(const QString &)));
}

void ChannelTab::topicChanged(const QString &topic)
{
  if (topic.isEmpty()) {
    m_ui.topic->hide();
  }
  else {
    m_ui.topic->setText(IrcUtil::messageToHtml(topic));
    m_ui.topic->show();
  }
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
