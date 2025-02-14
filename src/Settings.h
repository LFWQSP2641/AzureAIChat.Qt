#pragma once

#include "src/APIConfig.h"

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(APIConfig config READ config WRITE setConfig NOTIFY configChanged FINAL)
    Q_PROPERTY(quint64 maxTokenSize READ maxTokenSize WRITE setMaxTokenSize NOTIFY maxTokenSizeChanged FINAL)

public:
    explicit Settings(QObject *parent = nullptr);
    ~Settings();

    APIConfig config() const;
    void setConfig(const APIConfig &newConfig);

    quint64 maxTokenSize() const;
    void setMaxTokenSize(quint64 newMaxTokenSize);

public slots:
    void saveFile() const;
    void loadFile();

protected:
    APIConfig m_config;
    quint64 m_maxTokenSize = 1024;

signals:
    void configChanged();
    void maxTokenSizeChanged();

private:
};
