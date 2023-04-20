// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Controls
import mineClient

Window {
    width: 1280
    height: 720

    visible: true
    title: "mineClient"

    Screen01 {
        id: mainScreen
        x: 0
        y: 0
    }

    Button {
        id: button
        x: 341
        y: 8
        text: "JOIN"
        onClicked: Mine.toggle()
    }

    Text {
        id: text1
        x: 217
        y: 168
        width: 810
        height: 385
        text: qsTr("Text")
        font.pixelSize: 12

        Connections{
            target: Mine

            onReceiveJSON: function(text){text1.text = text;}
        }
    }
        
}

