#include "channeltab.h"
#include <QtDebug>

ChannelTab::ChannelTab(Conversation *conversation, QWidget *parent)
  : AbstractTab(conversation, parent)
{
  connect(m_conversation, SIGNAL(nicksChanged(const QStringList &)),
      this, SLOT(nicksChanged(const QStringList &)));

  setupUi();
}

void ChannelTab::appendText(QString text)
{
  m_ui.textBrowser->append(text);
}

void ChannelTab::on_lineEdit_returnPressed()
{
  QString text = m_ui.lineEdit->text();
  emit textEntered(text);
  m_ui.lineEdit->clear();
}

void ChannelTab::nicksChanged(const QStringList &nicks)
{
  nicksModel.setStringList(nicks);
}

void ChannelTab::setupUi()
{
  m_ui.setupUi(this);
  m_ui.nicks->setModel(&nicksModel);
}
