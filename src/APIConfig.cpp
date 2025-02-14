#include "APIConfig.h"

#include <QDebug>

APIConfig::APIConfig()
{
}

APIConfig::APIConfig(QStringView endpoint, QStringView key)
    : m_endpoint{ endpoint.toString() }, m_key{ key.toString() }
{
}

bool APIConfig::operator==(const APIConfig &other) const
{
    return m_endpoint == other.m_endpoint && m_key == other.m_key;
}

QString APIConfig::endpoint() const
{
    return m_endpoint;
}

void APIConfig::setEndpoint(const QString &newEndpoint)
{
    if (m_endpoint == newEndpoint)
        return;
    m_endpoint = newEndpoint;
}

QString APIConfig::key() const
{
    return m_key;
}

void APIConfig::setKey(const QString &newKey)
{
    if (m_key == newKey)
        return;
    m_key = newKey;
}

QDebug operator<<(QDebug debug, const APIConfig &config)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "APIConfig(" << config.endpoint() << ", " << config.key() << ")";
    return debug;
}
