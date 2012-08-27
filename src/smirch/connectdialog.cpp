#include "connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent)
  : QDialog(parent)
{
  m_ui.setupUi(this);

  settings.beginGroup("connect");
  m_ui.leServer->setText(settings.value("host", "irc.freenode.net").toString());
  m_ui.sbPort->setValue(settings.value("port", 6667).toInt());
  m_ui.leNickname->setText(settings.value("nick").toString());
  m_ui.leUsername->setText(settings.value("user").toString());
  m_ui.leRealName->setText(settings.value("real").toString());
  m_ui.leNickPassword->setText(settings.value("nickpasswd").toString());
  m_ui.cbSsl->setChecked(settings.value("ssl", false).toBool());
  settings.endGroup();
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

QString ConnectDialog::nickPassword() const
{
  return m_ui.leNickPassword->text();
}

bool ConnectDialog::useSsl() const
{
  return m_ui.cbSsl->isChecked();
}

void ConnectDialog::on_buttonBox_accepted()
{
  if (!server().isEmpty() && !nickname().isEmpty() &&
      !username().isEmpty() && !realName().isEmpty()) {

    settings.beginGroup("connect");
    settings.setValue("host", server());
    settings.setValue("port", port());
    settings.setValue("nick", nickname());
    settings.setValue("user", username());
    settings.setValue("real", realName());
    settings.setValue("nickpasswd", nickPassword());
    settings.setValue("ssl", useSsl());
    settings.endGroup();

    accept();
  }
}
