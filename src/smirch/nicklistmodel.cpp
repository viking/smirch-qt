#include "nicklistmodel.h"

NickListModel::NickListModel(QObject *parent)
  : QAbstractListModel(parent)
{
}

void NickListModel::setStringList(const QStringList &list)
{
  emit beginResetModel();
  m_list = list;
  emit endResetModel();
}

const QStringList &NickListModel::stringList() const
{
  return m_list;
}

int NickListModel::rowCount(const QModelIndex &) const
{
  return m_list.count();
}

QVariant NickListModel::data(const QModelIndex &index, int role) const
{
  switch (role) {
    case Qt::DisplayRole:
      return QVariant(m_list.at(index.row()));

    default:
      return QVariant();
  }
}

void NickListModel::addNick(const QString &nick)
{
  int i;
  bool ok = true;
  for (i = 0; i < m_list.count(); i++) {
    int result = m_list.at(i).compare(nick);
    if (result == 0) {
      /* Don't add duplicates */
      ok = false;
      break;
    }
    else if (result > 0) {
      break;
    }
  }

  if (ok) {
    beginInsertRows(QModelIndex(), i, i);
    m_list.insert(i, nick);
    endInsertRows();
  }
}

void NickListModel::removeNick(const QString &nick)
{
  int i = m_list.indexOf(nick);
  if (i >= 0) {
    beginRemoveRows(QModelIndex(), i, i);
    m_list.removeAt(i);
    endRemoveRows();
  }
}
