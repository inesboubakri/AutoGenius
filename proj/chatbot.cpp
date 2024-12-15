#include "chatbot.h"

ChatBot::ChatBot() {
    // Constructor
}

QString ChatBot::respondToUser(const QString& question) {
    // Simple chatbot logic
    if (question.contains("hello", Qt::CaseInsensitive)) {
        return "Bonjour ! Comment puis-je vous aider aujourd'hui ?";
    } else if (question.contains("comment ça va", Qt::CaseInsensitive)) {
        return "Je suis juste un programme, mais je vais bien, merci !";
    } else if (question.contains("bye", Qt::CaseInsensitive)) {
        return "Au revoir ! Passez une excellente journée !";
    }
    // Questions sur la gestion des partenariats
    else if (question.contains("ajouter un partenaire", Qt::CaseInsensitive)) {
        return "Pour ajouter un partenaire, allez dans le menu 'Gestion des Partenaires' et cliquez sur 'Ajouter'.";
    } else if (question.contains("supprimer un partenaire", Qt::CaseInsensitive)) {
        return "Pour supprimer un partenaire, utilisez la référence du partenaire dans la section 'Suppression'.";
    } else if (question.contains("liste des partenaires", Qt::CaseInsensitive)) {
        return "Vous pouvez voir la liste des partenaires dans le tableau sous 'Gestion des Partenaires'.";
    } else if (question.contains("contrat", Qt::CaseInsensitive)) {
        return "Vous pouvez générer un contrat pour un partenaire en cliquant sur 'Exporter PDF' dans les détails du partenariat.";
    } else if (question.contains("statut d'un partenaire", Qt::CaseInsensitive)) {
        return "Pour vérifier le statut d'un partenaire, recherchez sa référence dans la section 'Gestion des Partenaires'.";
    }
    // Réponse par défaut
    else {
        return "Désolé, je ne sais pas répondre à cela. Essayez une autre question concernant la gestion des partenaires.";
    }
}
