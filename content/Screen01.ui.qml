

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import mineClient

Rectangle {
    id: rectangle
    width: 1280
    height: 720

    color: Constants.backgroundColor

    TextField {
        id: textField1
        x: 45
        y: 8
        placeholderText: qsTr("GameID")
    }

    TextField {
        id: textField2
        x: 194
        y: 8
        placeholderText: qsTr("UserID")
    }

    TextArea {
        id: log
        x: 45
        y: 77
        width: 1196
        height: 601
        placeholderTextColor: "#60000000"
        placeholderText: qsTr("Text Area")
    }
}
