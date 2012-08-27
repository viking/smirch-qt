#ifndef __CHANNELTAB_H
#define __CHANNELTAB_H

#include <QCompleter>
#include "abstracttab.h"
#include "ui_channeltab.h"

class ChannelTab : public AbstractTab
{
  Q_OBJECT

  public:
    ChannelTab(Conversation *conversation, QWidget *parent = 0);

  protected:
    QWebView *webView() const;
    LineEdit *lineEdit() const;

  private slots:
    void topicChanged(const QString &topic);

  private:
    Ui::ChannelTab m_ui;
    QCompleter *m_completer;

    void setupUi();
};

#endif
