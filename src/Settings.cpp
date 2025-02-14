#include "Settings.h"

#include "src/utils/Global.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

Settings::Settings(QObject *parent)
    : QObject{ parent }
{
    loadFile();
}

Settings::~Settings()
{
    saveFile();
}

APIConfig Settings::config() const
{
    return m_config;
}

void Settings::setConfig(const APIConfig &newConfig)
{
    if (m_config == newConfig)
        return;
    m_config = newConfig;
    emit configChanged();
}

void Settings::saveFile() const
{
    QFile file{ Global::configJsonPath() };
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning("Failed to open config file for writing");
        return;
    }
    QJsonObject configObject;
    configObject.insert(QStringLiteral("endpoint"), m_config.endpoint());
    configObject.insert(QStringLiteral("key"), m_config.key());
    QJsonObject rootObject;
    rootObject.insert(QStringLiteral("config"), configObject);
    rootObject.insert(QStringLiteral("maxTokenSize"), static_cast<qint64>(m_maxTokenSize));
    QJsonDocument doc{ rootObject };
    file.write(doc.toJson(QJsonDocument::Compact));
    file.close();
}

void Settings::loadFile()
{
    QFile file{ Global::configJsonPath() };
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("Failed to open config file for reading");
        return;
    }
    QJsonDocument doc{ QJsonDocument::fromJson(file.readAll()) };
    file.close();
    QJsonObject rootObject{ doc.object() };
    QJsonObject configObject{ rootObject.value(QStringLiteral("config")).toObject() };
    APIConfig newConfig;
    newConfig.setEndpoint(configObject.value(QStringLiteral("endpoint")).toString());
    newConfig.setKey(configObject.value(QStringLiteral("key")).toString());
    setConfig(newConfig);
    setMaxTokenSize(rootObject.value(QStringLiteral("maxTokenSize")).toVariant().toULongLong());
}

quint64 Settings::maxTokenSize() const
{
    return m_maxTokenSize;
}

void Settings::setMaxTokenSize(quint64 newMaxTokenSize)
{
    if (m_maxTokenSize == newMaxTokenSize)
        return;
    m_maxTokenSize = newMaxTokenSize;
    emit maxTokenSizeChanged();
}
