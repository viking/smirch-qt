#include <QMenu>
#include <QWebFrame>
#include <QContextMenuEvent>
#include <QWebElement>
#include <QDesktopServices>
#include "webview.h"

#include <QtDebug>

WebView::WebView(QWidget *parent)
  : QWebView(parent)
{
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
}

void WebView::contextMenuEvent(QContextMenuEvent *ev)
{
  QWebPage *p = page();
  if (p != NULL && !(p->swallowContextMenuEvent(ev))) {
    /* Get the element using a hit test */
    QWebHitTestResult hitResult = p->currentFrame()->hitTestContent(ev->pos());
    if (hitResult.linkElement().isNull()) {
      return;
    }

    /* Show context menu for link */
    QMenu menu(this);
    QAction *copyLink = pageAction(QWebPage::CopyLinkToClipboard);
    menu.addAction(copyLink);
    QAction *openLink = menu.addAction("Open link in browser");

    QAction *execResult = menu.exec(ev->globalPos());
    if (execResult == openLink) {
      QDesktopServices::openUrl(hitResult.linkUrl());
    }
    else if (execResult == copyLink) {
      triggerPageAction(QWebPage::CopyLinkToClipboard);
    }
  }
}

void WebView::loadFinished(bool ok)
{
  page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}
