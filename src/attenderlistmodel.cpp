
#include "attenderlistmodel.h"

Attender::Attender(const QString& name):m_name(name) {}
Attender::Attender() {};

void Attender::name(const QString& name) {m_name=name;}
QString Attender::getName() const{return m_name;}

AttenderListModel::AttenderListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void AttenderListModel::addAttender(const Attender& att) {
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_attenders.append(att);
    endInsertRows();
    Q_EMIT dataChanged(this->index(rowCount()-1),this->index(rowCount()));
}

int AttenderListModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_attenders.count();
}
int AttenderListModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_attenders.count();
}

QVariant AttenderListModel::data(const QModelIndex& index, int role) const{
    if(index.row() <0 || index.row() >= m_attenders.count()) {
        return QVariant();
    }

    if(role == NameRole) {
        return m_attenders[index.row()].getName();
    }

    return QVariant();
}

bool AttenderListModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    if(index.isValid()){
        if(role ==Qt::EditRole) {
        const Attender& attender = qvariant_cast<Attender>(value);
            m_attenders.replace(index.row(), attender);
            Q_EMIT dataChanged(index,index);
            return true;
        } else if(role == NameRole) {
            m_attenders[index.row()].name(value.toString());
            Q_EMIT dataChanged(index,index);
            return true;
        }
    }
    return false;
}

bool AttenderListModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(QModelIndex(),row,row+count-1);
    for(int i=0;i<count;++i) {
        m_attenders.append({""});
    }
    endInsertRows();

    return true;
}

bool AttenderListModel::removeRows(int row, int count, const QModelIndex &parent) {
    if(m_attenders.size()<=row) {
        return false;
    } else if(m_attenders.size()<row+count) {
        count = m_attenders.size()-row;
    }

    beginRemoveRows(QModelIndex(),row,row+count);
    m_attenders.remove(row,count);
    endRemoveRows();

    return true;
}

QHash<int,QByteArray> AttenderListModel::roleNames() const {
    QHash<int,QByteArray> roles;
    roles[NameRole] = "attname";

    return roles;
}


