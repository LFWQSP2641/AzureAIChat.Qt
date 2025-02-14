#pragma once

#include <QList>
#include <QString>

class MessagesList
{
public:
    MessagesList();

    enum Role
    {
        User = 0,
        Assistant,
        System
    };

    typedef QPair<Role, QString> RoleMessage;

    QList<RoleMessage> messages() const;

    void addMessage(const RoleMessage &message);
    void addMessage(const QString &message);
    void clearMessages();

protected:
    QList<RoleMessage> m_messages;
};
