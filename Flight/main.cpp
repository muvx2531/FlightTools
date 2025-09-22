#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include <QQuickWindow>
#include <QSGRendererInterface>
<<<<<<< HEAD
#include <QtDebug>
#include <QQueue>
#include <QThread>

#include "datasource.h"
#include "samplerworker.h"
=======
#include "SineWaveTest.h"
>>>>>>> bc523e3f8eae207881223cc6b330ef17e9f38592

int main(int argc, char *argv[])
{
    int rv;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    bool openGLSupported = QQuickWindow::graphicsApi() == QSGRendererInterface::OpenGLRhi;
    if (!openGLSupported) {
        qWarning() << "OpenGL is not set as the graphics backend, so AbstractSeries.useOpenGL will not work.";
        qWarning() << "Set QSG_RHI_BACKEND=opengl environment variable to force the OpenGL backend to be used.";
    }

    QQuickStyle::setStyle("Basic");

    QQueue<QPointF> samplesQueue;
    auto threadSampler = new QThread();
    auto samplerWorker = new SamplerWorker(&samplesQueue);
    DataSource dataSource(&samplesQueue);

    samplerWorker->moveToThread(threadSampler);

    QObject::connect(samplerWorker, &SamplerWorker::workRequested, threadSampler, [threadSampler]() {
        threadSampler->start();
    });
    QObject::connect(threadSampler, &QThread::started, samplerWorker, &SamplerWorker::doWork);
    QObject::connect(samplerWorker, &SamplerWorker::finished, threadSampler, &QThread::quit, Qt::DirectConnection);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, samplerWorker, &SamplerWorker::abort);
    QObject::connect(samplerWorker, &SamplerWorker::updateCurve, &dataSource, &DataSource::updateCurve);

    QQmlApplicationEngine engine;
<<<<<<< HEAD

=======
    
    // Register QML types (this should be called before loading QML)
    qmlRegisterType<SineWaveTest>("Flight.Backend", 1, 0, "SineWaveTest");
    
    // Register OpenGL support flag
>>>>>>> bc523e3f8eae207881223cc6b330ef17e9f38592
    engine.rootContext()->setContextProperty("openGLSupported", openGLSupported);
    engine.rootContext()->setContextProperty("dataSource", &dataSource);
    engine.rootContext()->setContextProperty("sampleWorker", samplerWorker);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        [](const QUrl &url) {
            qDebug() << "QML object creation FAILED for URL:" << url;
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    QObject::connect(&engine, &QQmlApplicationEngine::warnings, [](const QList<QQmlError> &warnings) {
        for (const QQmlError &warning : warnings) {
            qDebug() << "QML Warning:" << warning.toString();
        }
    });
    qDebug() << "About to load QML from module...";

    const QUrl url(QStringLiteral("qrc:/qt/qml/Flight/Main.qml"));
    qDebug() << "Trying to load QML from URL:" << url;

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        qDebug() << "Direct URL loading failed, trying module loading...";
        engine.loadFromModule("Flight", "Main");
    }

    qDebug() << "QML loading attempted. Checking root objects...";
    qDebug() << "Root objects count:" << engine.rootObjects().count();

    if (engine.rootObjects().isEmpty()) {
        qDebug() << "Failed to load QML! No root objects found.";
        qDebug() << "This might be due to QML compilation errors or missing dependencies.";
        samplerWorker->abort();
        threadSampler->quit();
        threadSampler->wait();
        delete samplerWorker;
        delete threadSampler;
        return -1;
    }
    qDebug() << "QML loaded successfully with" << engine.rootObjects().count() << "root objects";

    qDebug() << "QML setup complete, ready to start application...";

    samplerWorker->requestWork();

    qDebug() << "Starting application event loop...";
    qDebug() << "Main window should be visible now. Close it to exit.";
    rv = app.exec();
    qDebug() << "Application event loop ended with code:" << rv;

    samplerWorker->abort();
    if (threadSampler->isRunning()) {
        threadSampler->quit();
        threadSampler->wait();
    }

    delete samplerWorker;
    delete threadSampler;

    qDebug() << "Application shutdown complete";

    qDebug() << "End Application";

    return rv;
}
