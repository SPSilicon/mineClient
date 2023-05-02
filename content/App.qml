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

    Flickable {
        id: flickable
        TextArea {

            id: text1
            width: window.contentItem.width-100
            height: window.contentItem.height-100
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 45
            anchors.topMargin: 77
            placeholderTextColor: "#60000000"
            placeholderText: qsTr("Text Area")
            Connections{
                target: Mine

                onReceiveJSON: function(json){
                    var txt = " ";
                    for(var i in json ){
                        txt += i+" : "+json[i]+"\n";
                    }
                    //gridView.width = 18*json["width"];
                    listModel.clear();
                    //for(let i in json["board"]) {
                    //    listModel.append({name:json["board"][i]+""});
                    //}
                    //gridView.modelChanged();

                    text1.text = txt;
                }
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
        onClicked: function() {
            var clientMessage={
                id : gameid.text,
                actions : [],
                host : userid.text
            };


            Mine.toggle(clientMessage);
        }
    }

    Button {
        id: serverConnButton
        x: 1173
        y: 8
        text: qsTr("server")
        highlighted: false
        flat: false

        onClicked: function() {
            Mine.conn()
        }
    }

    Text {
        id: connInfo
        x: 1021
        y: 12
        width: 146
        height: 44
        text: qsTr("Disconnected")
        font.pixelSize: 23
        Connections {
            target :Mine

            onConnected : connInfo.text = "Connected";
            onClosed : connInfo.text = "DisConnected";
        }
    }

    ListModel {
        id : listModel
    }

    GridView {
        id: gridView
        x: 231
        y: 144

        width: 831
        height: 497
        interactive: false
        contentWidth: 18

        model: listModel
        cellWidth: 18
        cellHeight: 18
        delegate: Column {
            width: 18
            height: 18

           Rectangle{
                id: gRect
                anchors.horizontalCenter: parent.horizontalCenter
                border.color: "black"
                border.width: 1
                color : acolor
                width: 18
                height: 18
                //width: 18
                //height: 18

                MouseArea{
                    anchors.fill: parent
                    onClicked : function() {
                        if()
                        index.text = name+"c";
                    }
                    onPressed : function() {
                        gRect.color = "grey";
                    }
                    onReleased: function() {
                        gRect.color = "white";
                    }

                }

                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    id : index
                    font.pixelSize: 12
                    font.bold: true
                    padding: 0
                    rightPadding: 0
                    leftPadding: 0
                    bottomPadding: 4
                    topPadding: 0
                    text: name;
                }


            }


        }

        Connections {
            target :Mine

            onInitGame: function(height, width) {
                gridView.height = height*18;
                gridView.width = width*18;

                listModel.clear();
                for(var i=0;i<height*width;++i) {
                    listModel.append({name:i+"",acolor: "white"});
                }

            }


            onUpdateGame: function(board) {
                for(var idx=0;idx<board.length;++idx){
                    if(board[idx]===9) {
                        listModel.set(idx,{name:"",acolor: "white"});
                    } else if(board[idx]===10) {
                        listModel.set(idx,{name:"🚩",acolor: "white"});
                    } else if(board[idx]===0){
                        listModel.set(idx,{name:"",acolor: "grey"});
                    } else if(board[idx]===-1) {
                        listModel.set(idx,{name:"💣",acolor: "grey"});
                    } else {
                        listModel.set(idx,{name:board[idx]+"",acolor: "grey"});
                    }
                    //listModel.get(i).name = board[i];
                }
            }
        }


    }

}

