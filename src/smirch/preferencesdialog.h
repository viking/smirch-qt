#ifndef __PREFERENCESDIALOG_H
#define __PREFERENCESDIALOG_H

#include <QDialog>
#include <QFontDialog>
#include <QSettings>
#include "ui_preferencesdialog.h"

class PreferencesDialog : public QDialog
{
  Q_OBJECT

  public:
    PreferencesDialog(QWidget *parent = 0);

    QFont font() const;

  private slots:
    void on_btnFont_clicked();
    void on_buttonBox_accepted();

  private:
    Ui::PreferencesDialog m_ui;
    QSettings settings;
    QString m_fontFamily;
    int m_fontSize;

    void updateFontName();
};

#endif
