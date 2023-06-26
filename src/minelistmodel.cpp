#include "minelistmodel.h"


Tile::Tile(const QString& text, const QString& tcolor, const QString& acolor) :m_text(text), m_tcolor(tcolor), m_acolor(acolor){
}
Tile::Tile(){};
QString Tile::acolor() const {return m_acolor;}
QString Tile::tcolor() const {return m_tcolor;}
QString Tile::text() const {return m_text;}
void Tile::setText(const QString& text) {m_text = text;}
void Tile::setAcolor(const QString& acolor){m_acolor = acolor;}
void Tile::setTcolor(const QString& tcolor){m_tcolor = tcolor;}


MineGameTable::MineGameTable(QObject *parent)
    :QAbstractTableModel(parent)
{
}

qint32 MineGameTable::getWidth() {
    return m_width;
}

qint32 MineGameTable::getHeight(){
    return m_height;
}

void MineGameTable::setWidth(const qint32& v){m_width = v;}

void MineGameTable::setHeight(const qint32& v ){m_height = v;}

void MineGameTable::addRow(QList<Tile> tile) {
    beginInsertRows(QModelIndex(),rowCount(), rowCount());
    m_tiles.append(tile);
    endInsertRows();
    Q_EMIT dataChanged(this->index(rowCount()-1,0),this->index(rowCount()-1,tile.count()));
}


int MineGameTable::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_tiles.count();
}



int MineGameTable::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_width;
}

void MineGameTable::clearList() {
    beginRemoveRows(QModelIndex(),0,rowCount());
    m_tiles.clear();
    endRemoveRows();
}

QVariant MineGameTable::data(const QModelIndex &index, int role) const{
    if (index.row() <0 || index.row() >= m_tiles.count()) {
        qDebug() << "unexpected";
        return QVariant();
    }

    const Tile &tile = m_tiles[index.row()].at(index.column());;
    if(role == TextRole) {
        return tile.text();
    } else if(role == AcolorRole) {
        return tile.acolor();
    } else if(role == TcolorRole) {
        return tile.tcolor();
    }

    return QVariant();
}

bool MineGameTable::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid() ) {
        if(role == Qt::EditRole) {
            const Tile&& tile = qvariant_cast<Tile>(value);
            m_tiles[index.row()].replace(index.column(),tile);
            Q_EMIT dataChanged(index,index);
            return true;
        } else if(role == TextRole) {
            m_tiles[index.row()].value(index.column()).setText(value.toString());
            Q_EMIT dataChanged(index,index);
            return true;
        }else if(role == AcolorRole) {
            m_tiles[index.row()].value(index.column()).setAcolor(value.toString());
            Q_EMIT dataChanged(index,index);
            return true;
        }else if(role == TcolorRole) {
            m_tiles[index.row()].value(index.column()).setTcolor(value.toString());
            Q_EMIT dataChanged(index,index);
            return true;
        }
    } else {
        qDebug() << "unexpected";
    }
    return false;
}


QHash<int, QByteArray> MineGameTable::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TextRole] = "mtext";
    roles[AcolorRole] = "acolor";
    roles[TcolorRole] = "tcolor";
    return roles;
}
