#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include <QQuickWindow>
#include <QSGRendererInterface>
#include <QQueue>
#include <QThread>
#include <QtDebug>
#include "datasource.h"

int main(int argc, char *argv[])
{
    int rv;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    // OpenGL backend is required for AbstractSeries.useOpenGL optimization
    // Check if OpenGL is available and warn if not
    bool openGLSupported = QQuickWindow::graphicsApi() == QSGRendererInterface::OpenGLRhi;
    if (!openGLSupported) {
        qWarning() << "OpenGL is not set as the graphics backend, so AbstractSeries.useOpenGL will not work.";
        qWarning() << "Set QSG_RHI_BACKEND=opengl environment variable to force the OpenGL backend to be used.";
    }

    QQuickStyle::setStyle("Basic");

    // Create sample queue and DataSource (keep DataSource on main thread for QML)
    QQueue<QPointF> samplesQueue;
    DataSource *dataSource = new DataSource(&samplesQueue);

    QQmlApplicationEngine engine;

    // Register OpenGL support flag and DataSource
    engine.rootContext()->setContextProperty("openGLSupported", openGLSupported);
    engine.rootContext()->setContextProperty("dataSource", dataSource);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Flight", "Main");

    // Start the sine wave generation (DataSource handles its own threading internally)
    dataSource->requestWork();

    rv = app.exec();
    
    // Clean shutdown
    dataSource->abort();
    delete dataSource;
    qDebug() << "Delete DataSource";

    qDebug() << "End Application";

    return rv;
}
