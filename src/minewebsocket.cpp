#include "minewebsocket.h"
#include "src/minelistmodel.h"

#include <QDebug>
using namespace std;

QT_USE_NAMESPACE

MineSweeper::MineSweeper(const QUrl &url, MineGameTable& model,AttenderListModel& attenderModel, QObject *parent)
    :   QObject(parent), m_gameTable(model), m_attenderModel(attenderModel)
{
    m_Url = url;
    m_gameID = QStringLiteral("");
    connect(&m_pWebSocketClient, &QWebSocket::connected,
            this, &MineSweeper::onConnected);
    connect(&m_pWebSocketClient, &QWebSocket::disconnected,
            this, &MineSweeper::onClosed);
    connect(&m_pWebSocketClient, &QWebSocket::textMessageReceived,
            this, &MineSweeper::onReceiveMessage);
    //m_pWebSocketClient.open(url);
}

MineSweeper::~MineSweeper()
{
    m_pWebSocketClient.close();
}

void MineSweeper::onConnected() {
    Q_EMIT connected();
    qDebug() << "connected!";
}

void MineSweeper::onClosed(){
    Q_EMIT closed();
}

void MineSweeper::join(const QString &userID,const QString &gameID) {
    if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::ConnectedState) {
        send(-1,0,userID,gameID.trimmed(),false);
    } else if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::UnconnectedState){
        return;
    }
    qDebug() << "invoked!";
}

void MineSweeper::send(const qint32 &h,const qint32 &w, const QString& sender,const QString& gameid, const bool& flag) {
    qDebug() << "sending.." << h << "," << w;
    QJsonArray actions;
    QJsonObject action;
    if(flag) {
        action.insert("actionType","FLAG");
    } else {
        action.insert("actionType","DIG");
    }
    action.insert("loc",h*m_gameTable.getWidth()+w);
    actions.append(action);
    QJsonObject json;
    json.insert("id",gameid.trimmed());
    json.insert("actions",actions);
    json.insert("host",sender);

    QString str(QJsonDocument(json).toJson(QJsonDocument::Compact));
    qDebug() << "sended.." << str << m_pWebSocketClient.sendTextMessage(str);
}


bool MineSweeper::conn() {
    if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::ConnectedState) {
        m_pWebSocketClient.close();

        return false;
    } else if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::UnconnectedState){
        m_pWebSocketClient.open(m_Url);
        return true;
    }
    return false;
}

QString MineSweeper::curGameid() const{
    return m_gameID;
};

void MineSweeper::onReceiveMessage(const QString& message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if(doc.isNull()) {
        //qDebug() << "init ";
    }
    else {
        QJsonObject json = doc.object();

        Q_EMIT receiveJSON(json);
        //qDebug() << json["id"].toString();

        m_attenderModel.removeRows(0,m_attenderModel.rowCount());
        for(auto &&i : json["attenders"].toArray()) {
            Attender attender = Attender(i.toString());
            m_attenderModel.addAttender(attender);
        }

        if(m_gameID.compare(json["id"].toString())!=0) {
            qDebug() << "initGame";
            m_gameID = json["id"].toString().trimmed();
            Q_EMIT initGame(json["height"].toInt(),json["width"].toInt());
            
            m_gameTable.setWidth(json["width"].toInt());
            m_gameTable.setHeight(json["height"].toInt());
            
            m_gameTable.clearList();
            auto&& board = json["board"].toArray();
            for(int i=0;i<m_gameTable.getHeight();++i) {
                QList<Tile> tiles;
                for(int j=0; j<m_gameTable.columnCount(); ++j) {
                    tiles.append({" ","white","white"});
                }
                m_gameTable.addRow(tiles);
            }

        } else {
            //qDebug() << "updateGame";
            Q_EMIT updateGame(json["board"].toArray());
            auto&& board = json["board"].toArray();
            
            m_gameTable.setWidth(json["width"].toInt());
            m_gameTable.setHeight(json["height"].toInt());
            int w = m_gameTable.getWidth();
            int h = m_gameTable.getHeight();
            for(int i=0;i<h;++i)  {
                for(int j=0; j<w; ++j){
                    int value = board[i*w+j].toInt();

                    if(value==9) {
                        m_gameTable.setData(m_gameTable.index(i,j),QVariant::fromValue<Tile>({" ","black","white"}));
                    } else if(value==10) {
                        m_gameTable.setData(m_gameTable.index(i,j),QVariant::fromValue<Tile>({"🚩","black","white"}));
                    } else if(value==0){
                        m_gameTable.setData(m_gameTable.index(i,j),QVariant::fromValue<Tile>({"","black","grey"}));
                    } else if(value==-1) {
                        m_gameTable.setData(m_gameTable.index(i,j),QVariant::fromValue<Tile>({"💣","black","grey"}));
                    } else {
                        m_gameTable.setData(m_gameTable.index(i,j),QVariant::fromValue<Tile>({QString::number(value),"black","grey"}));
                    }

                }
            }
        }
    }

}
