#include "minewebsocket.h"
#include <QDebug>
using namespace std;

QT_USE_NAMESPACE

MineWebSocket::MineWebSocket(const QUrl &url, QObject *parent)
:   QObject(parent)
{
    m_Url = url;
    m_gameID = QStringLiteral("");
    connect(&m_pWebSocketClient, &QWebSocket::connected,
            this, &MineWebSocket::onConnected);
    connect(&m_pWebSocketClient, &QWebSocket::disconnected,
            this, &MineWebSocket::onClosed);
    connect(&m_pWebSocketClient, &QWebSocket::textMessageReceived,
            this, &MineWebSocket::onReceiveMessage);
    //m_pWebSocketClient.open(url);
}

MineWebSocket::~MineWebSocket()
{
    m_pWebSocketClient.close();
}

void MineWebSocket::onConnected() {
    Q_EMIT connected();
    qDebug() << "connected!";
}

void MineWebSocket::onClosed(){
    Q_EMIT closed();
}

void MineWebSocket::toggle(const QJsonObject &content) {
    if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::ConnectedState) {
        send(content);
    } else if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::UnconnectedState){
        return;
    }
    qDebug() << "invoked!" << content.keys();
}

void MineWebSocket::send(const QJsonObject &content) {
    QString str(QJsonDocument(content).toJson(QJsonDocument::Compact));
    qDebug() << "sending.." << str << m_pWebSocketClient.sendTextMessage(str);
}



bool MineWebSocket::conn() {
    if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::ConnectedState) {
        m_pWebSocketClient.close();

        return false;
    } else if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::UnconnectedState){
        m_pWebSocketClient.open(m_Url);

        return true;
    }
    return false;
}


void MineWebSocket::onReceiveMessage(const QString& message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if(doc.isNull()) {
        qDebug() << "init ";
    }
    else {
        QJsonObject json = doc.object();

        Q_EMIT receiveJSON(json);
        //qDebug() << json["id"].toString();
        if(m_gameID.compare(json["id"].toString())!=0) {
            m_gameID = json["id"].toString();
            Q_EMIT initGame(json["height"].toInt(),json["width"].toInt());
        } else {
            Q_EMIT updateGame(json["board"].toArray());
        }
        /*QString str;
        for(auto i : json) {
             qDebug() << i.toString();
             str.append(" "+i.toString());
        }

        if(m_gameID.compare(json["gameid"].toString())==0) {
            Q_EMIT receiveJSON(str);
        } else {
            Q_EMIT receiveJSON(str);
        }
        */
    }

}
