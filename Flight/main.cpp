#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include <QQuickWindow>
#include <QSGRendererInterface>
#include "SineWaveTest.h"

int main(int argc, char *argv[])
{
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

    QQmlApplicationEngine engine;
    
    // Register QML types (this should be called before loading QML)
    qmlRegisterType<SineWaveTest>("Flight.Backend", 1, 0, "SineWaveTest");
    
    // Register OpenGL support flag
    engine.rootContext()->setContextProperty("openGLSupported", openGLSupported);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Flight", "Main");

    return app.exec();
}
