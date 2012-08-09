#include "connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent)
  : QDialog(parent)
{
  ui.setupUi(this);
}

QString ConnectDialog::server() const
{
  return ui.leServer->text();
}

QString ConnectDialog::nickname() const
{
  return ui.leNickname->text();
}

QString ConnectDialog::username() const
{
  return ui.leUsername->text();
}

QString ConnectDialog::realName() const
{
  return ui.leRealName->text();
}

void ConnectDialog::on_buttonBox_accepted()
{
  if (!server().isEmpty() && !nickname().isEmpty() &&
      !username().isEmpty() && !realName().isEmpty()) {
    accept();
  }
}
