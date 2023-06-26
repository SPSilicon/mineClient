
#ifndef ATTENDERLISTMODEL_H
#define ATTENDERLISTMODEL_H

#include <QAbstractListModel>

class Attender {
public:
    Attender(const QString& name);
    Attender();

    void name(const QString& name);
    QString getName() const;
private:
    QString m_name;
};
Q_DECLARE_METATYPE(Attender);

class AttenderListModel : public QAbstractListModel
{
    Q_OBJECT;
public:

    enum attenderRole{
        NameRole = Qt::UserRole+1
    };

    explicit AttenderListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent= QModelIndex()) const;
    int columnCount(const QModelIndex& parent= QModelIndex()) const;
    void addAttender(const Attender& att);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<Attender> m_attenders;
};

#endif // ATTENDERLISTMODEL_H
