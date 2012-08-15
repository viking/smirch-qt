#include "connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent)
  : QDialog(parent)
{
  m_ui.setupUi(this);
}

QString ConnectDialog::server() const
{
  return m_ui.leServer->text();
}

int ConnectDialog::port() const
{
  return m_ui.sbPort->value();
}

QString ConnectDialog::nickname() const
{
  return m_ui.leNickname->text();
}

QString ConnectDialog::username() const
{
  return m_ui.leUsername->text();
}

QString ConnectDialog::realName() const
{
  return m_ui.leRealName->text();
}

void ConnectDialog::on_buttonBox_accepted()
{
  if (!server().isEmpty() && !nickname().isEmpty() &&
      !username().isEmpty() && !realName().isEmpty()) {
    accept();
  }
}
