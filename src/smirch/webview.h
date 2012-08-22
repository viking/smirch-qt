#ifndef __WEBVIEW_H
#define __WEBVIEW_H

#include <QWebView>

class WebView : public QWebView
{
  Q_OBJECT

  public:
    WebView(QWidget *parent = 0);

  protected:
    void contextMenuEvent(QContextMenuEvent *ev);

  private slots:
    void loadFinished(bool ok);
};

#endif
