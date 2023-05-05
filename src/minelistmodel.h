#ifndef MINELISTMODEL_H
#define MINELISTMODEL_H

#include "qabstractitemmodel.h"

class Tile {
public:
    Tile(const QString& value, const QString &tcolor, const QString &acolor);

    QString value() const;
    QString acolor() const;
    QString tcolor() const;
private:
    QString m_value;
    QString m_acolor;
    QString m_tcolor;
};

class Minelistmodel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TileRoles {
        ValueRole = Qt::UserRole +1,
        AcolorRole,
        TcolorRole
    };

    Minelistmodel(QObject *parent = nullptr);

    void addTile(const Tile &tile);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<Tile> m_tiles;
};

#endif // MINELISTMODEL_H
