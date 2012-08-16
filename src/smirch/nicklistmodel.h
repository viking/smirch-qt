#ifndef __NICKLISTMODEL_H
#define __NICKLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class NickListModel : public QAbstractListModel
{
  Q_OBJECT

  public:
    NickListModel(QObject *parent = 0);

    void setStringList(const QStringList &list);
    const QStringList &stringList() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void addNick(const QString &nick);
    void removeNick(const QString &nick);

  private:
    QStringList m_list;
};

#endif
