#include "minelistmodel.h"


Tile::Tile(const QString& value, const QString& tcolor, const QString& acolor) :m_value(value), m_tcolor(tcolor), m_acolor(acolor){
}

QString Tile::acolor() const {return m_acolor;}
QString Tile::tcolor() const {return m_tcolor;}
QString Tile::value() const {return m_value;}

Minelistmodel::Minelistmodel(QObject *parent)
    :QAbstractListModel(parent)
{
}

void Minelistmodel::addTile(const Tile &tile) {
    beginInsertRows(QModelIndex(),rowCount(), rowCount());
    m_tiles << tile;
    endInsertRows();
}

int Minelistmodel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_tiles.count();
}

QVariant Minelistmodel::data(const QModelIndex &index, int role) const{
    if (index.row() <0 || index.row() >= m_tiles.count())
        return QVariant();

    const Tile &tile = m_tiles[index.row()];
    if(role == ValueRole) {
        return tile.value();
    } else if(role == AcolorRole) {
        return tile.acolor();
    } else if(role == TcolorRole) {
        return tile.tcolor();
    }

    return QVariant();
}

bool Minelistmodel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid() ) {
        if(role == ValueRole) {
            return m_tiles.replace(index.row(),)
        }else if(role == AcolorRole) {

        }else if(role == TcolorRole) {

        }
    }
}
QHash<int, QByteArray> Minelistmodel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ValueRole] = "value";
    roles[AcolorRole] = "acolor";
    roles[TcolorRole] = "tcolor";
    return roles;
}
