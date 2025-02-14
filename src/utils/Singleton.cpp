#include "Singleton.h"

#include "src/Settings.h"

Q_GLOBAL_STATIC(Settings, m_settings)
Q_GLOBAL_STATIC(Singleton, m_instance)

Singleton::Singleton(QObject *parent)
    : QObject{ parent }
{
}

Singleton *Singleton::create([[maybe_unused]] QQmlEngine *engine, QJSEngine *scriptEngine)
{
    return m_instance();
}

Settings *Singleton::settings() const
{
    return m_settings;
}

Settings *Singleton::staticSettings()
{
    return m_settings;
}
