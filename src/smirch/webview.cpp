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
  : QWebView(parent)
{
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
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

void WebView::contextMenuEvent(QContextMenuEvent *ev)
{
  QWebPage *p = page();
  if (p != NULL && !(p->swallowContextMenuEvent(ev))) {
    QMenu menu(this);

    /* Get the element using a hit test */
    QWebHitTestResult hitResult = p->currentFrame()->hitTestContent(ev->pos());
    if (hitResult.linkElement().isNull()) {
      /* Show default menu */
      QAction *printHtml = new QAction("Print HTML", this);
      menu.addAction(printHtml);

      if (menu.exec(ev->globalPos()) == printHtml) {
        qDebug() << p->mainFrame()->toHtml();
      }
    }
    else {
      /* Show context menu for link */
      QAction *copyLink = pageAction(QWebPage::CopyLinkToClipboard);
      menu.addAction(copyLink);
      QAction *openLink = menu.addAction("Open Link in Browser");

      QAction *execResult = menu.exec(ev->globalPos());
      if (execResult == openLink) {
        QDesktopServices::openUrl(hitResult.linkUrl());
      }
      else if (execResult == copyLink) {
        triggerPageAction(QWebPage::CopyLinkToClipboard);
      }
    }

    ev->accept();
  }
}

void WebView::loadFinished(bool ok)
{
  page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
  m_head = page()->mainFrame()->findFirstElement("head");

  m_settings.beginGroup("preferences");
  QFont font(m_settings.value("fontfamily", "DejaVu Sans Mono").toString(),
      m_settings.value("fontsize", 18).toInt());
  m_settings.endGroup();
  setFont(font);
}
