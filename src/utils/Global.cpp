#include "Global.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

QString Global::appConfigPath;
QString Global::appDataPath;
QString Global::appDebugPath;
QString Global::appTempPath;

void Global::initOnce()
{
#ifdef Q_OS_WINDOWS
    Global::appConfigPath = QCoreApplication::applicationDirPath().append(QStringLiteral("/Config"));
    Global::appDataPath = QCoreApplication::applicationDirPath().append(QStringLiteral("/Data"));
    Global::appTempPath = QCoreApplication::applicationDirPath().append(QStringLiteral("/Temp"));
    Global::appDebugPath = QCoreApplication::applicationDirPath().append(QStringLiteral("/Debug"));
#else
    Global::appConfigPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    Global::appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    Global::appTempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    Global::appDebugPath = QString(appTempPath).append(QStringLiteral("/Debug"));
#endif // Q_OS_WINDOWS

    QDir dir;
    dir.mkpath(Global::configPath());
    dir.mkpath(Global::dataPath());
    dir.mkpath(Global::tempPath());
    dir.mkpath(Global::debugPath());
}

QString Global::configPath()
{
    return Global::appConfigPath;
}

QString Global::dataPath()
{
    return Global::appDataPath;
}

QString Global::debugPath()
{
    return Global::appDebugPath;
}

QString Global::tempPath()
{
    return Global::appTempPath;
}

QString Global::configJsonPath()
{
    return Global::configPath().append(QStringLiteral("/config.json"));
}

bool Global::deleteDir(const QString &path)
{
    if (path.isEmpty())
    {
        return false;
    }
    QDir dir(path);
    if (!dir.exists())
    {
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); // 设置过滤
    QFileInfoList fileList = dir.entryInfoList();           // 获取所有的文件信息
    foreach (QFileInfo file, fileList)
    {
        // 遍历文件信息
        if (file.isFile())
        {
            // 是文件，删除
            file.dir().remove(file.fileName());
        }
        else
        {
            // 递归调用函数，删除子文件夹
            deleteDir(file.absoluteFilePath());
        }
    }
    return dir.rmpath(dir.absolutePath()); // 这时候文件夹已经空了，再删除文件夹本身
}

qint64 Global::getDirSize(const QString &filePath)
{
    QDir tmpDir(filePath);
    qint64 size{ 0 };

#if 0
    /*获取文件列表  统计文件大小*/
    for(const auto &fileInfo : tmpDir.entryInfoList(QDir::Files))
    {
        size += fileInfo.size();
    }

    /*获取文件夹  并且过滤掉.和..文件夹 统计各个文件夹的文件大小 */
    for(const auto &subDir : tmpDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        size += getDirSize(QString(filePath).append(QStringLiteral("/")).append(subDir)); //递归进行  统计所有子目录
    }
#endif
    auto filesInfoList{ tmpDir.entryInfoList(QDir::Files) };
    size = std::accumulate(filesInfoList.cbegin(), filesInfoList.cend(), size, [](qint64 value, const QFileInfo &fileInfo)
                           {
                               return fileInfo.size() + value;
                           });
    auto dirsList{ tmpDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot) };
    size = std::accumulate(dirsList.cbegin(), dirsList.cend(), size, [&filePath](qint64 value, const QString &subDir)
                           {
                               return getDirSize(QString(filePath).append(QStringLiteral("/")).append(subDir)) + value;
                           });

    return size;
}
