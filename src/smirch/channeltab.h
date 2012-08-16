#ifndef __CHANNELTAB_H
#define __CHANNELTAB_H

#include <QStringListModel>
#include "abstracttab.h"
#include "ui_channeltab.h"

class ChannelTab : public AbstractTab
{
  Q_OBJECT

  public:
    ChannelTab(Conversation *conversation, QWidget *parent = 0);

  protected:
    void appendText(QString text);

  private slots:
    void on_lineEdit_returnPressed();
    void nicksChanged(const QStringList &nicks);

  private:
    Ui::ChannelTab m_ui;
    QStringListModel nicksModel;

    void setupUi();
};

#endif
