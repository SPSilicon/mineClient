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
    connect(&m_pWebSocketClient, &QWebSocket::textMessageReceived,
            this, &MineWebSocket::onReceiveMessage);
    //m_pWebSocketClient.open(url);
}

MineWebSocket::~MineWebSocket()
{
    m_pWebSocketClient.close();
}

void MineWebSocket::onConnected() {
    qDebug() << "connected!";
}

void MineWebSocket::onClosed(){}

void MineWebSocket::toggle(const QString& gameid,const QString userid) {
    if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::ConnectedState) {
        m_pWebSocketClient.close();
    } else if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::UnconnectedState){
        m_pWebSocketClient.open(m_Url);
    }
    qDebug() << "invoked!" << gameid << userid;
}

void MineWebSocket::send(const QJsonObject &content) {
    QString str(QJsonDocument(content).toJson(QJsonDocument::Compact));
    m_pWebSocketClient.sendTextMessage(str);
}


void MineWebSocket::onReceiveMessage(const QString& message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if(doc.isNull()) {
        qDebug() << "init ";
    }
    else {
        QJsonObject json = doc.object();
        Q_EMIT receiveJSON(json);
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
