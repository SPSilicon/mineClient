
#ifndef MINESWEEPER_H
#define MINESWEEPER_H


#include <QObject>
#include "minelistmodel.h"
#include "minewebsocket.h"

class MineSweeper
{
    Q_OBJECT
public:
    MineSweeper(const Minelistmodel& mineListModel, const MineWebSocket& mineWebSocket);

private:
    Minelistmodel& m_mineListModel;
    MineWebSocket& m_mineWebSocket;
};

#endif // MINESWEEPER_H
