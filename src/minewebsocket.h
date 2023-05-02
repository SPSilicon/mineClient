
#ifndef MINEWEBSOCKET_H
#define MINEWEBSOCKET_H


#include <QObject>
#include <QTWebSockets>
#include <QString>
#include <QtCore>
#include <QJsonDocument>



class MineWebSocket : public QObject
{
/*
    struct Action {
        qint32 loc;
        enum actionType {
            DIG,
            FLAG
        };
    };

    struct ClientMessage {
        QString id;
        QString host;
        QList<Action> actions;
    };

    struct ServerMessage {
        QString id;
        QString host;
        qint32 y;
        qint32 x;
        QList<QString> attenders;
        qint32* board;
        QString message;
    };
*/
    Q_OBJECT
public:
    explicit MineWebSocket(const QUrl &url, QObject *parent = nullptr);
    virtual ~MineWebSocket();
    Q_INVOKABLE void toggle(const QJsonObject &content);
    Q_INVOKABLE void send(const QJsonObject &content);
    Q_INVOKABLE bool conn();

Q_SIGNALS:
    void receiveJSON(const QJsonObject& json);
    void initGame(const qint32 height, const qint32 width);
    void updateGame(const QJsonArray board);
    void connected();
    void closed();

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
