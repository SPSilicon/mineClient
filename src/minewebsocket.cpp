#include "minewebsocket.h"
#include <QDebug>
using namespace std;

QT_USE_NAMESPACE

MineWebSocket::MineWebSocket(const QUrl &url, QObject *parent)
:   QObject(parent)
{
    m_Url = url;
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

void MineWebSocket::toggle() {
    if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::ConnectedState) {
        m_pWebSocketClient.close();
    } else if(m_pWebSocketClient.state() == QAbstractSocket::SocketState::UnconnectedState){
        m_pWebSocketClient.open(m_Url);
    }
    qDebug() <<"invoked!";
}



void MineWebSocket::onReceiveMessage(const QString& message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if(doc.isNull()) {
        qDebug() << "init!";
        Q_EMIT receiveJSON("init!");
    }
    else {
        QJsonObject json = doc.object();

        QString str;
        for(auto i : json) {
            qDebug() << i.toString();
            str.append(" "+i.toString());
        }
        Q_EMIT receiveJSON(str);
    }

}
