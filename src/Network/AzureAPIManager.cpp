#include "AzureAPIManager.h"

QNetworkRequest AzureAPIManager::buildAzureRequest(const APIConfig &apiConfig) const
{
    QNetworkRequest request;
    request.setUrl(QUrl{ apiConfig.endpoint() });

    QHttpHeaders headers;
    headers.replaceOrAppend(QHttpHeaders::WellKnownHeader::Authorization, QStringLiteral("Bearer ").append(apiConfig.key()));
    headers.replaceOrAppend(QHttpHeaders::WellKnownHeader::ContentType, QStringLiteral("application/json"));

    request.setHeaders(headers);
    return request;
}
