#include "mainwindow.h"
#include "connectdialog.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
}

void MainWindow::on_actionConnect_triggered()
{
  ConnectDialog dialog(this);
  dialog.exec();

  if (dialog.result() == QDialog::Accepted) {
    IrcSession *session = ui.serverTab->session();
    if (session != NULL) {
      session->close();
    }

    session = new IrcSession(this);
    connect(session, SIGNAL(disconnected()), session, SLOT(deleteLater()));

    session->setHost(dialog.server());
    session->setUserName(dialog.username());
    session->setNickName(dialog.nickname());
    session->setRealName(dialog.realName());
    ui.serverTab->setSession(session);
    session->open();
  }
}

void MainWindow::on_serverTab_channelJoined(const QString &name)
{
  Tab *tab = new Tab(Tab::ChannelTab);
  tab->setName(name);
  ui.tabWidget->addTab(tab, name);
  ui.tabWidget->setCurrentIndex(ui.tabWidget->count());
}
