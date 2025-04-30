#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <memory>
#include "User.h"
#include "Admin.h"
#include "Player.h"
#include "Quiz.h"
#include "Score.h"

class DataManager : public QObject {
    Q_OBJECT

public:
    static DataManager& getInstance();

    // User management
    void saveUser(const User& user);
    std::unique_ptr<User> loadUser(const QString& email);
    bool userExists(const QString& email);

    // Quiz management
    void saveQuiz(const Quiz& quiz);
    Quiz loadQuiz(const QString& quizId);
    QList<Quiz> loadAllQuizzes();

    // Score management
    void saveScore(const Score& score);
    QList<Score> loadScores(const QString& playerId);
    QList<Score> loadAllScores();

private:
    DataManager();
    ~DataManager() = default;
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;

    QString getUsersFilePath() const;
    QString getQuizzesFilePath() const;
    QString getScoresFilePath() const;

    QJsonObject userToJson(const User& user) const;
    std::unique_ptr<User> jsonToUser(const QJsonObject& json) const;
    QJsonObject quizToJson(const Quiz& quiz) const;
    Quiz jsonToQuiz(const QJsonObject& json) const;
    QJsonObject scoreToJson(const Score& score) const;
    Score jsonToScore(const QJsonObject& json) const;
};

#endif // DATAMANAGER_H 