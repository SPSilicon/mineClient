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
                    for(var i in json ){
                        text1.append(i);
                    }
                }
            }
        }
    }


    Button {
        id: button
        x: 341
        y: 8
        text: "JOIN"
        onClicked: Mine.toggle(gameid.text,userid.text)
    }

}

