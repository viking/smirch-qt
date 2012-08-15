#include "channeltab.h"
#include <QtDebug>

ChannelTab::ChannelTab(Conversation *conversation, QWidget *parent)
  : AbstractTab(conversation, parent)
{
  connect(m_conversation, SIGNAL(nicksChanged(QStringList, QStringList)),
      this, SLOT(nicksChanged(QStringList, QStringList)));

  setupUi();
}

void ChannelTab::appendText(QString text)
{
  if (m_uiInitialized) {
    m_ui.textBrowser->append(text);
  }
}

void ChannelTab::on_lineEdit_returnPressed()
{
  QString text = m_ui.lineEdit->text();
  emit textEntered(text);
  m_ui.lineEdit->clear();
}

void ChannelTab::nicksChanged(QStringList added, QStringList removed)
{
  if (m_uiInitialized) {
    qDebug() << recipient() << "added:" << added;
    qDebug() << recipient() << "removed:" << removed;
    m_ui.nicks->addItems(added);
    // FIXME: remove stuff!
  }
  else {
    qDebug() << recipient() << "ui wasn't initialized yet!";
  }
}

void ChannelTab::setupUi()
{
  m_ui.setupUi(this);
  m_uiInitialized = true;
}
