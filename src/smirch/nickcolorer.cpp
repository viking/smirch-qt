#include <cmath>
#include "nickcolorer.h"

QColor NickColorer::colorFor(const IrcSender &sender)
{
  QSettings settings;
  QColor result;

  settings.beginGroup("nickcolors");
  if (settings.contains(sender.name())) {
    result.setNamedColor(settings.value(sender.name()).toString());
  }
  else {
    qreal hue = (qreal) qrand() / (qreal) RAND_MAX;
    hue += GOLDEN_RATIO_CONJ;
    hue = hue - (qint8) hue;
    result.setHsvF(hue, 0.1, 0.9);
    settings.setValue(sender.name(), result.name());
  }
  return result;
}
