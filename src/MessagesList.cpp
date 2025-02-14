#include "MessagesList.h"

MessagesList::MessagesList()
{
}

QList<MessagesList::RoleMessage> MessagesList::messages() const
{
    return m_messages;
}

void MessagesList::addMessage(const RoleMessage &message)
{
    m_messages.append(message);
}

void MessagesList::addMessage(const QString &message)
{
    if (m_messages.isEmpty())
    {
        addMessage(RoleMessage(Role::User, message));
        return;
    }
    auto lastMessage = m_messages.last();
    if (lastMessage.first == Role::User)
    {
        addMessage(RoleMessage(Role::Assistant, message));
    }
    else if (lastMessage.first == Role::Assistant)
    {
        addMessage(RoleMessage(Role::User, message));
    }
    else
    {
        qWarning("Unknown message role");
    }
}

void MessagesList::clearMessages()
{
    m_messages.clear();
}
