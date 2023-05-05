// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "minewebsocket.h"
#include "app_environment.h"
#include "minelistmodel.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:Main/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    Minelistmodel model;
    engine.rootContext()->setContextProperty("mineModel", &model);

    MineWebSocket mine( QUrl(QStringLiteral("ws://192.168.35.177:8080/minesweeper")) );
    engine.rootContext()->setContextProperty("Mine", &mine);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");


    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }




    return app.exec();
}
