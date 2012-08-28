#include "nicklistmodel.h"
#include <QtDebug>

NickListModel::NickListModel(QObject *parent)
  : QAbstractListModel(parent)
{
}

void NickListModel::setNicks(const QStringList &nicks)
{
  emit beginResetModel();
  m_list.clear();
  for (int i = 0; i < nicks.count(); i++) {
    const QString &nick = nicks.at(i);
    if (nick.isEmpty()) {
      continue;
    }
    m_list.append(nickPairFromString(nick));
  }
  emit endResetModel();
}

int NickListModel::rowCount(const QModelIndex &) const
{
  return m_list.count();
}

QVariant NickListModel::data(const QModelIndex &index, int role) const
{
  switch (role) {
    case Qt::DisplayRole:
      return QVariant(nickWithSymbols(index.row()));

    case Qt::EditRole:
      return QVariant(m_list.at(index.row()).first);

    default:
      return QVariant();
  }
}

void NickListModel::addNick(const QString &nick)
{
  int i;
  bool ok = true;
  const QPair<QString, int> newPair = nickPairFromString(nick);
  for (i = 0; i < m_list.count(); i++) {
    const QPair<QString, int> element = m_list.at(i);
    if (element.second > newPair.second) {
      continue;
    }

    int c = element.first.compare(newPair.first);
    if (c == 0) {
      /* Don't add duplicates */
      ok = false;
      break;
    }
    else if (c > 0) {
      break;
    }
  }

  if (ok) {
    beginInsertRows(QModelIndex(), i, i);
    m_list.insert(i, newPair);
    endInsertRows();
  }
}

void NickListModel::removeNick(const QString &nick)
{
  int i = indexOfNick(nick);
  if (i >= 0) {
    beginRemoveRows(QModelIndex(), i, i);
    m_list.removeAt(i);
    endRemoveRows();
  }
}

int NickListModel::indexOfNick(const QString &nick, int from) const
{
  for (int i = from; i < m_list.count(); i++) {
    if (m_list.at(i).first == nick) {
      return i;
    }
  }
  return -1;
}

void NickListModel::setMode(const QString &mode, const QString &nick)
{
  if (mode.isEmpty() || nick.isEmpty())
    return;

  int i = indexOfNick(nick);
  if (i < 0) {
    return;
  }

  QPair<QString, int> pair = m_list[i];
  int newFlags = pair.second;

  bool add;
  const QChar op = mode.at(0);
  if (op == '-') {
    add = false;
  }
  else if (op == '+') {
    add = true;
  }
  else {
    /* Bogus mode */
    return;
  }

  if (add) {
    for (int j = 1; j < mode.count(); j++) {
      const QChar c = mode.at(j);
      if (c == 'v') {
        newFlags |= VoicePrivileges;
      }
      else if (c == 'o') {
        newFlags |= OpPrivileges;
      }
    }
  }
  else {
    for (int j = 1; j < mode.count(); j++) {
      const QChar c = mode.at(j);
      if (c == 'v') {
        newFlags &= ~VoicePrivileges;
      }
      else if (c == 'o') {
        newFlags &= ~OpPrivileges;
      }
    }
  }

  if (newFlags != pair.second) {
    /* I'm lazy */
    pair.second = newFlags;
    QString newNick = nickWithSymbols(pair);
    removeNick(pair.first);
    addNick(newNick);
  }
}

QPair<QString, int> NickListModel::nickPairFromString(const QString &nick)
{
  int flags = NoPrivileges;
  int i;
  for (i = 0; i < nick.count(); i++) {
    const QChar c = nick.at(i);
    if (c.isLetter()) {
      break;
    }
    else if (c == '@') {
      flags |= OpPrivileges;
    }
    else if (c == '+') {
      flags |= VoicePrivileges;
    }
  }
  return QPair<QString, int>(nick.mid(i), flags);
}

QString NickListModel::nickWithSymbols(int i) const
{
  const QPair<QString, int> &pair = m_list.at(i);
  return nickWithSymbols(pair);
}

QString NickListModel::nickWithSymbols(const QPair<QString, int> &pair) const
{
  QString nick = QString(pair.first);
  if (pair.second & VoicePrivileges) {
    nick.prepend('+');
  }
  if (pair.second & OpPrivileges) {
    nick.prepend('@');
  }
  return nick;
}
