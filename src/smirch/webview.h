#ifndef __WEBVIEW_H
#define __WEBVIEW_H

#include <QWebView>
#include <QWebElement>
#include <QFont>
#include <QSettings>

class WebView : public QWebView
{
  Q_OBJECT

  public:
    WebView(QWidget *parent = 0);

  public slots:
    void setFont(const QFont &font);

  protected:
    void contextMenuEvent(QContextMenuEvent *ev);

  private slots:
    void loadFinished(bool ok);

  private:
    static const QString s_fontStyleTemplate;
    QWebElement m_head;
    QSettings m_settings;
};

#endif
