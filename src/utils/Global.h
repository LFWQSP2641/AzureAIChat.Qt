#pragma once

#include <QObject>

namespace Global
{
Q_NAMESPACE
extern QString appConfigPath;
extern QString appDataPath;
extern QString appDebugPath;
extern QString appTempPath;

extern void initOnce();

extern QString configPath();
extern QString dataPath();
extern QString debugPath();
extern QString tempPath();

extern QString configJsonPath();

extern bool deleteDir(const QString &path);
extern qint64 getDirSize(const QString &filePath);
}; // namespace Global
