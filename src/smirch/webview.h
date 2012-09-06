#ifndef __WEBVIEW_H
#define __WEBVIEW_H

#include <QWebView>
#include <QWebElement>
#include <QFont>
#include <QSettings>
#include <QMutex>
#include <QSize>

class WebView : public QWebView
{
  Q_OBJECT

  public:
    WebView(QWidget *parent = 0);

    void appendHtml(const QString &markup);

  public slots:
    void setFont(const QFont &font);

  protected:
    bool event(QEvent *event);
    void contextMenuEvent(QContextMenuEvent *ev);

  private slots:
    void loadFinished(bool ok);
    void frameSizeChanged(const QSize &size);

  private:
    static const QString s_fontStyleTemplate;

    bool m_pageLoaded;
    QWebElement m_head;
    QWebElement m_body;
    QSettings m_settings;
    QStringList m_appendQueue;
    QMutex m_appendMutex;
    QSize m_frameSize;
    int m_lastScrollBarMaximum;

    void internalAppendHtml(const QString &markup);
};

#endif
