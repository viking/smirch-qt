#ifndef __CONNECTDIALOG_H
#define __CONNECTDIALOG_H

#include <QDialog>
#include <QSettings>
#include "ui_connectdialog.h"

class ConnectDialog : public QDialog
{
  Q_OBJECT

  public:
    ConnectDialog(QWidget *parent = 0);
    QString server() const;
    int port() const;
    QString nickname() const;
    QString username() const;
    QString realName() const;
    QString nickPassword() const;

  private slots:
    void on_buttonBox_accepted();

  private:
    Ui::ConnectDialog m_ui;
    QSettings settings;
};

#endif
