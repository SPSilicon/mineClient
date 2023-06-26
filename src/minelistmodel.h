#ifndef MINELISTMODEL_H
#define MINELISTMODEL_H

#include <QAbstractListModel>

class Tile {
public:
    Tile(const QString& text, const QString &tcolor, const QString &acolor);
    Tile();

    QString text() const;
    QString acolor() const;
    QString tcolor() const;

    void setText(const QString& text);
    void setAcolor(const QString& acolor);
    void setTcolor(const QString& tcolor);
private:
    QString m_text;
    QString m_acolor;
    QString m_tcolor;

};
Q_DECLARE_METATYPE(Tile);


class MineGameTable : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum TileRoles {
        TextRole = Qt::UserRole +1,
        AcolorRole,
        TcolorRole
    };

    MineGameTable(QObject *parent = nullptr);

    void addRow(QList<Tile> tile);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    void setWidth(const qint32& v);
    void setHeight(const qint32& v);
    qint32 getHeight();
    void clearList();
    Q_INVOKABLE qint32 getWidth();


    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<QList<Tile>> m_tiles;
    qint32 m_width;
    qint32 m_height;
};

#endif // MINELISTMODEL_H
