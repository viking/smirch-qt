#include "nicklistmodel.h"

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
  for (i = 0; i < m_list.count(); i++) {
    /* Assume the nick has no privileges on join */
    const QPair<QString, int> element = m_list.at(i);
    if (element.second != NoPrivileges) {
      continue;
    }

    int c = element.first.compare(nick);
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
    m_list.insert(i, QPair<QString, int>(nick, NoPrivileges));
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
  const QPair<QString, int> &element = m_list.at(i);
  QString nick = QString(element.first);
  if (element.second & VoicePrivileges) {
    nick.prepend('+');
  }
  if (element.second & OpPrivileges) {
    nick.prepend('@');
  }
  return nick;
}
