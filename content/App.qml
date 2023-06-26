// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Controls
import mineClient

Window{
    id: window
    width: 1280
    height: 720

    visible: true
    color: "#959494"
    maximumHeight: 720
    maximumWidth: 1280


    minimumHeight: 720
    minimumWidth: 1280

    title: "mineClient"
    TextField {
        id: gameid
        x: 45
        anchors.right: userid.left
        anchors.top: parent.top
        anchors.rightMargin: 29
        anchors.topMargin: 8
        placeholderText: qsTr("GameID")
    }

    TextField {
        id: userid
        x: 194
        anchors.right: button.left
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.rightMargin: 27
        placeholderText: qsTr("UserID")
    }

    ListView {
        //TODO: ListView로 바꿔서 Attenders 목록출력하기
        id: listView1
        width: 251
        height: 587
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 45
        anchors.topMargin: 77
        model : attenders

        delegate: Column{
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text : attname
            }
        }
    }



    Button {
        id: button
        x: 341
        y: 8
        width: 87
        height: 48
        text: "JOIN"
        onClicked: Mine.join(userid.text, gameid.text);

    }

    Button {
        id: serverConnButton
        x: 1173
        text: qsTr("server")
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.rightMargin: 42
        highlighted: false
        flat: false

        onClicked: function() {
            Mine.conn()
        }
    }

    Text {
        id: connInfo
        x: 1021
        width: 146
        height: 44
        text: qsTr("Disconnected")
        anchors.right: serverConnButton.left
        anchors.top: parent.top
        font.pixelSize: 23
        anchors.topMargin: 12
        anchors.rightMargin: 6
        Connections {
            target :Mine

            onConnected : connInfo.text = "Connected";
            onClosed : connInfo.text = "DisConnected";
        }
    }

    TableView {
        id: grdv1

        property int bsize : 30
        property int tsize : 22
        width: window.contentItem.width-400
        height: window.contentItem.height-150

        anchors.left: parent.left
        anchors.top: parent.top

        anchors.leftMargin: 302
        anchors.topMargin: 87

        model: mineModel

        delegate: Column {

            width: grdv1.bsize
            height: grdv1.bsize

             Rectangle{
                  id: bRect
                  anchors.horizontalCenter: parent.horizontalCenter
                  border.color: "black"
                  border.width: 1
                  color : acolor
                  width: grdv1.bsize
                  height: grdv1.bsize
                  //width: 18
                  //height: 18

                  MouseArea{
                      anchors.fill: parent
                      acceptedButtons: Qt.LeftButton | Qt.RightButton
                      onClicked : function(mouse) {

                          if(mouse.button == Qt.LeftButton ) {
                              Mine.send(row,column, userid.text, gameid.text, false);
                          } else if(mouse.button == Qt.RightButton) {
                              Mine.send(row,column, userid.text, gameid.text, true);
                          }
                      }



                  }

                  Text{
                      anchors.horizontalCenter: parent.horizontalCenter
                      font.pixelSize: 12
                      font.bold: grdv1.tsize;
                      padding: 0
                      rightPadding: 0
                      leftPadding: 0
                      bottomPadding: 4
                      topPadding: 0
                      text: mtext;
                  }


             }


        }
    }

        Text {
            id: curGameID;
            text: "gameid"
            anchors.left: button.right
            anchors.right: connInfo.left
            anchors.top: parent.top
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            anchors.rightMargin: 268
            anchors.topMargin: 12
            anchors.leftMargin: 276

            Connections{
                target: Mine

                onReceiveJSON: function() {
                   curGameID.text = Mine.curGameid();
                   gameid.text = Mine.curGameid();
               }
            }
        }




}

