#pragma once

#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>

class Settings;

class Singleton : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit Singleton(QObject *parent = nullptr);
    static Singleton *create(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr);

    Q_INVOKABLE Settings *settings() const;
    static Settings *staticSettings();

private:
};
