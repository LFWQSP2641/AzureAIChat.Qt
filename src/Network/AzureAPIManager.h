#pragma once

#include <QNetworkAccessManager>
#include <QObject>
#include <src/APIConfig.h>

class AzureAPIManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    using QNetworkAccessManager::QNetworkAccessManager;

    QNetworkRequest buildAzureRequest(const APIConfig &apiConfig) const;

    // QNetworkReply *sendAzureRequest(const APIConfig &apiConfig, const QByteArray &data) const;
};
