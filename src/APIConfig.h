#pragma once

#include <QObject>
#include <QString>
#include <qqmlintegration.h>

class APIConfig
{
    Q_GADGET
    Q_PROPERTY(QString endpoint READ endpoint WRITE setEndpoint FINAL)
    Q_PROPERTY(QString key READ key WRITE setKey FINAL)
    QML_VALUE_TYPE(apiConfig)

public:
    APIConfig();
    APIConfig(QStringView endpoint, QStringView key);

    bool operator==(const APIConfig &other) const;

    QString endpoint() const;
    void setEndpoint(const QString &newEndpoint);

    QString key() const;
    void setKey(const QString &newKey);

private:
    QString m_endpoint;
    QString m_key;
};

Q_DECLARE_METATYPE(APIConfig)
QDebug operator<<(QDebug debug, const APIConfig &config);
