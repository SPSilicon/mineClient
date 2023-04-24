
#ifndef MINEWEBSOCKET_H
#define MINEWEBSOCKET_H


#include <QObject>
#include <QTWebSockets>
#include <QString>
#include <QtCore>
#include <QJsonDocument>

class MineWebSocket : public QObject
{
    Q_OBJECT
public:
    explicit MineWebSocket(const QUrl &url, QObject *parent = nullptr);
    virtual ~MineWebSocket();
    Q_INVOKABLE void toggle(const QString& gameid,const QString userid);
    Q_INVOKABLE void send(const QJsonObject &content);

Q_SIGNALS:
    void receiveJSON(const QJsonObject& json);

public Q_SLOTS:
    void onConnected();
    void onClosed();
    void onReceiveMessage(const QString &message);

private:
    QWebSocket m_pWebSocketClient;
    QUrl m_Url;
    QString m_gameID;
};

#endif // MINEWEBSOCKET_H
