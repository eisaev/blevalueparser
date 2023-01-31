#include <QGuiApplication>
#include <QQuickStyle>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLoggingCategory>
#include <QLocale>
#include <QTranslator>

#include "blemanager.h"


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    // Workaround for
    // https://bugreports.qt.io/browse/QTBUG-98098 and
    // https://bugreports.qt.io/browse/QTBUG-101026
    QQuickStyle::setStyle("Basic");

    // TODO:
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    //const QStringList uiLanguages{ "fi_FI" };
    //qDebug() << uiLanguages;
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "bvpqt_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            //qDebug() << baseName;
            //qDebug() << app.installTranslator(&translator);
            break;
        }
    }
    //qDebug() << translator.language();

    QQmlApplicationEngine engine;

    BLEManager bleManagerSingleton;
    qmlRegisterSingletonType<BLEManager>("dev.eisaev.blemanager", 1, 0, "BLEManagerSingleton",
                                         [&](QQmlEngine *, QJSEngine *) -> QObject * { return &bleManagerSingleton; });

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](const QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
