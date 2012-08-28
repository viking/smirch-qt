#include "preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent)
  : QDialog(parent)
{
  m_ui.setupUi(this);

  settings.beginGroup("preferences");
  m_fontFamily = settings.value("fontfamily", "DejaVu Sans Mono").toString();
  m_fontSize = settings.value("fontsize", 18).toInt();
  settings.endGroup();

  updateFontName();
}

QFont PreferencesDialog::font() const
{
  return QFont(m_fontFamily, m_fontSize);
}

void PreferencesDialog::on_btnFont_clicked()
{
  bool ok;
  QFont newFont = QFontDialog::getFont(&ok, font(), this);
  if (ok) {
    m_fontFamily = newFont.family();
    m_fontSize = newFont.pointSize();
    updateFontName();
  }
}

void PreferencesDialog::on_buttonBox_accepted()
{
  settings.beginGroup("preferences");
  settings.setValue("fontfamily", m_fontFamily);
  settings.setValue("fontsize", m_fontSize);
  settings.endGroup();
}

void PreferencesDialog::updateFontName()
{
  m_ui.btnFont->setText(QString("%1 %2").arg(m_fontFamily).arg(m_fontSize));
}
