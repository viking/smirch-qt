#include <QMenu>
#include <QWebFrame>
#include <QContextMenuEvent>
#include <QWebElement>
#include <QDesktopServices>
#include "webview.h"

#include <QtDebug>

const QString WebView::s_fontStyleTemplate =
  QString("<style class=\"font\" type=\"text/css\">body { font-family: \"%1\"; font-size: %2pt; }</style>");

WebView::WebView(QWidget *parent)
  : QWebView(parent), m_pageLoaded(false), m_lastScrollBarMaximum(0)
{
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
}

void WebView::appendHtml(const QString &markup)
{
  m_appendMutex.lock();
  if (m_pageLoaded) {
    m_appendMutex.unlock();
    internalAppendHtml(markup);
  }
  else {
    m_appendQueue << markup;
    m_appendMutex.unlock();
  }
}

void WebView::setFont(const QFont &font)
{
  if (m_head.isNull())
    return;

  QString markup = s_fontStyleTemplate.arg(font.family()).arg(font.pointSize());
  QWebElement fontStyle = m_head.findFirst("style.font");
  if (fontStyle.isNull()) {
    m_head.appendInside(markup);
  }
  else {
    fontStyle.setOuterXml(markup);
  }
}

bool WebView::event(QEvent *event)
{
  /* Don't handle non-keyboard events */
  if (event->type() != QEvent::KeyPress) {
    return QWebView::event(event);
  }
  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
  if (keyEvent->key() == Qt::Key_Tab) {
    event->ignore();
    return true;
  }
  return QWebView::event(event);
}

void WebView::contextMenuEvent(QContextMenuEvent *ev)
{
  QWebPage *p = page();
  if (p != NULL && !(p->swallowContextMenuEvent(ev))) {
    QMenu menu(this);

    /* Get the element using a hit test */
    QWebHitTestResult hitResult = p->currentFrame()->hitTestContent(ev->pos());
    if (hitResult.linkElement().isNull()) {
      /* Show default menu */
      if (p->hasSelection()) {
        QAction *copyAction = pageAction(QWebPage::Copy);
        menu.addAction(copyAction);

        QAction *execResult = menu.exec(ev->globalPos());
        if (execResult == copyAction) {
          triggerPageAction(QWebPage::Copy);
        }
      }
      else {
        QAction *printHtmlAction = new QAction("Print HTML", this);
        menu.addAction(printHtmlAction);

        if (menu.exec(ev->globalPos()) == printHtmlAction) {
          qDebug() << p->mainFrame()->toHtml();
        }
      }
    }
    else {
      /* Show context menu for link */
      QAction *copyLinkAction = pageAction(QWebPage::CopyLinkToClipboard);
      menu.addAction(copyLinkAction);
      QAction *openLinkAction = menu.addAction("Open Link in Browser");

      QAction *execResult = menu.exec(ev->globalPos());
      if (execResult == openLinkAction) {
        QDesktopServices::openUrl(hitResult.linkUrl());
      }
      else if (execResult == copyLinkAction) {
        triggerPageAction(QWebPage::CopyLinkToClipboard);
      }
    }

    ev->accept();
  }
}

void WebView::loadFinished(bool ok)
{
  QWebFrame *frame = page()->mainFrame();
  connect(frame, SIGNAL(contentsSizeChanged(const QSize &)),
      this, SLOT(frameSizeChanged(const QSize &)));

  page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
  m_head = frame->findFirstElement("head");
  if (m_head.isNull()) {
    qDebug() << "Couldn't find HEAD element";
    return;
  }

  m_settings.beginGroup("preferences");
  QFont font(m_settings.value("fontfamily", "DejaVu Sans Mono").toString(),
      m_settings.value("fontsize", 18).toInt());
  m_settings.endGroup();
  setFont(font);

  m_body = frame->findFirstElement("body");
  if (m_body.isNull()) {
    qDebug() << "Couldn't find BODY element";
    return;
  }
  m_appendMutex.lock();
  m_pageLoaded = true;
  for (int i = 0; i < m_appendQueue.count(); i++) {
    internalAppendHtml(m_appendQueue.at(i));
  }
  m_appendQueue.clear();
  m_appendMutex.unlock();
}

void WebView::frameSizeChanged(const QSize &)
{
  QWebFrame *frame = page()->mainFrame();
  int scrollBarMaximum = frame->scrollBarMaximum(Qt::Vertical);
  if (frame->scrollBarValue(Qt::Vertical) == m_lastScrollBarMaximum) {
    frame->setScrollBarValue(Qt::Vertical, scrollBarMaximum);
  }
  m_lastScrollBarMaximum = scrollBarMaximum;
}

void WebView::internalAppendHtml(const QString &markup)
{
  m_body.appendInside(markup);
}
