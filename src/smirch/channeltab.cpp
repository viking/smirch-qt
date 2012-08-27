#include <IrcUtil>
#include <QScrollBar>
#include "channeltab.h"
#include "channel.h"
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
    m_ui.topic->setHtml(IrcUtil::messageToHtml(topic));

    /* Set topic height (based on QLineEdit */
    int leftMargin, topMargin, rightMargin, bottomMargin;
    m_ui.topic->getContentsMargins(&leftMargin, &topMargin, &rightMargin, &bottomMargin);
    QFontMetrics fm(m_ui.topic->font());
    int h = qMax(fm.height(), 14) + 4 + topMargin + bottomMargin;

    /* Increase height if scrollbar is visible */
    /*
    QScrollBar *scrollBar = m_ui.topic->horizontalScrollBar();
    if (scrollBar->isVisibleTo(m_ui.topic)) {
      h += scrollBar->sizeHint().height();
    }
    */
    m_ui.topic->setFixedHeight(h);

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

  /* Set model for nick view */
  NickListModel *nickListModel = static_cast<Channel *>(m_conversation)->nickListModel();
  m_ui.nicks->setModel(nickListModel);

  /* Set nick completer */
  m_completer = new QCompleter(nickListModel, this);
  m_ui.lineEdit->setCompleter(m_completer);
}
