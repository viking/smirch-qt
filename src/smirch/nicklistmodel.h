#ifndef __NICKLISTMODEL_H
#define __NICKLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class NickListModel : public QAbstractListModel
{
  Q_OBJECT

  public:
    NickListModel(QObject *parent = 0);

    void setNicks(const QStringList &nicks);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void addNick(const QString &nick);
    void removeNick(const QString &nick);

    int indexOfNick(const QString &nick, int from = 0) const;
    void setMode(const QString &mode, const QString &nick);

  private:
    enum PrivilegesFlags
    {
      NoPrivileges = 0x0,
      VoicePrivileges = 0x1,
      OpPrivileges = 0x2,
    };

    QList<QPair<QString, int> > m_list;

    QPair<QString, int> nickPairFromString(const QString &nick);
    QString nickWithSymbols(int i) const;
    QString nickWithSymbols(const QPair<QString, int> &pair) const;
};

#endif
