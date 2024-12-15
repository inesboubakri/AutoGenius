#ifndef CHATBOT_H
#define CHATBOT_H

#include <QString>

class ChatBot {
public:
    ChatBot();  // Constructor
    QString respondToUser(const QString& question);  // Respond to user input
};

#endif // CHATBOT_H
