
#ifndef MINEWEBSOCKET_H
#define MINEWEBSOCKET_H

#include "minelistmodel.h"
#include "attenderlistmodel.h"
#include <QObject>
#include <QTWebSockets>
#include <QString>
#include <QtCore>
#include <QJsonDocument>



class MineSweeper : public QObject
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
    explicit MineSweeper(const QUrl &url, MineGameTable& model,AttenderListModel& attenderModel, QObject *parent = nullptr);
    virtual ~MineSweeper();
    Q_INVOKABLE QString curGameid() const;
    Q_INVOKABLE void join(const QString &userID, const QString &gameID);
    Q_INVOKABLE void send(const qint32 &h,const qint32 &w, const QString& sender,const QString& gameid, const bool& flag);
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
    MineGameTable& m_gameTable;
    AttenderListModel& m_attenderModel;
};

#endif // MINEWEBSOCKET_H
