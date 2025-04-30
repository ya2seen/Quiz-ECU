#include "DataManager.h"
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

DataManager& DataManager::getInstance() {
    static DataManager instance;
    return instance;
}

DataManager::DataManager() {
    // Create data directory if it doesn't exist
    QDir dataDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dataDir.exists()) {
        dataDir.mkpath(".");
    }
}

QString DataManager::getUsersFilePath() const {
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/users.json";
}

QString DataManager::getQuizzesFilePath() const {
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/quizzes.json";
}

QString DataManager::getScoresFilePath() const {
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/scores.json";
}

void DataManager::saveUser(const User& user) {
    QFile file(getUsersFilePath());
    QJsonArray usersArray;
    
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            usersArray = doc.array();
            file.close();
        }
    }
    
    QJsonObject userObj = userToJson(user);
    bool found = false;
    
    for (int i = 0; i < usersArray.size(); ++i) {
        if (usersArray[i].toObject()["email"].toString() == QString::fromStdString(user.getEmail())) {
            usersArray[i] = userObj;
            found = true;
            break;
        }
    }
    
    if (!found) {
        usersArray.append(userObj);
    }
    
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(usersArray);
        file.write(doc.toJson());
        file.close();
    }
}

std::unique_ptr<User> DataManager::loadUser(const QString& email) {
    QFile file(getUsersFilePath());
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return nullptr;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    QJsonArray usersArray = doc.array();
    for (const QJsonValue& value : usersArray) {
        QJsonObject userObj = value.toObject();
        if (userObj["email"].toString() == email) {
            return jsonToUser(userObj);
        }
    }
    
    return nullptr;
}

bool DataManager::userExists(const QString& email) {
    return loadUser(email) != nullptr;
}

void DataManager::saveQuiz(const Quiz& quiz) {
    QFile file(getQuizzesFilePath());
    QJsonArray quizzesArray;
    
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            quizzesArray = doc.array();
            file.close();
        }
    }
    
    QJsonObject quizObj = quizToJson(quiz);
    bool found = false;
    
    for (int i = 0; i < quizzesArray.size(); ++i) {
        if (quizzesArray[i].toObject()["title"].toString() == QString::fromStdString(quiz.getTitle())) {
            quizzesArray[i] = quizObj;
            found = true;
            break;
        }
    }
    
    if (!found) {
        quizzesArray.append(quizObj);
    }
    
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(quizzesArray);
        file.write(doc.toJson());
        file.close();
    }
}

Quiz DataManager::loadQuiz(const QString& quizId) {
    QFile file(getQuizzesFilePath());
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Quiz not found");
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    QJsonArray quizzesArray = doc.array();
    for (const QJsonValue& value : quizzesArray) {
        QJsonObject quizObj = value.toObject();
        if (quizObj["title"].toString() == quizId) {
            return jsonToQuiz(quizObj);
        }
    }
    
    throw std::runtime_error("Quiz not found");
}

QList<Quiz> DataManager::loadAllQuizzes() {
    QFile file(getQuizzesFilePath());
    QList<Quiz> quizzes;
    
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return quizzes;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    QJsonArray quizzesArray = doc.array();
    for (const QJsonValue& value : quizzesArray) {
        quizzes.append(jsonToQuiz(value.toObject()));
    }
    
    return quizzes;
}

void DataManager::saveScore(const Score& score) {
    QFile file(getScoresFilePath());
    QJsonArray scoresArray;
    
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            scoresArray = doc.array();
            file.close();
        }
    }
    
    scoresArray.append(scoreToJson(score));
    
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(scoresArray);
        file.write(doc.toJson());
        file.close();
    }
}

QList<Score> DataManager::loadScores(const QString& playerId) {
    QFile file(getScoresFilePath());
    QList<Score> scores;
    
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return scores;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    QJsonArray scoresArray = doc.array();
    for (const QJsonValue& value : scoresArray) {
        QJsonObject scoreObj = value.toObject();
        if (scoreObj["playerId"].toString() == playerId) {
            scores.append(jsonToScore(scoreObj));
        }
    }
    
    return scores;
}

QList<Score> DataManager::loadAllScores() {
    QFile file(getScoresFilePath());
    QList<Score> scores;
    
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return scores;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    QJsonArray scoresArray = doc.array();
    for (const QJsonValue& value : scoresArray) {
        scores.append(jsonToScore(value.toObject()));
    }
    
    return scores;
}

QJsonObject DataManager::userToJson(const User& user) const {
    QJsonObject obj;
    obj["name"] = QString::fromStdString(user.getName());
    obj["email"] = QString::fromStdString(user.getEmail());
    obj["password"] = QString::fromStdString(user.getPassword());
    obj["type"] = QString::fromStdString(user.getUserType());
    return obj;
}

std::unique_ptr<User> DataManager::jsonToUser(const QJsonObject& json) const {
    std::string name = json["name"].toString().toStdString();
    std::string email = json["email"].toString().toStdString();
    std::string password = json["password"].toString().toStdString();
    std::string type = json["type"].toString().toStdString();
    
    if (type == "Admin") {
        return std::make_unique<Admin>(name, email, password);
    } else if (type == "Player") {
        return std::make_unique<Player>(name, email, password);
    }
    
    return nullptr;
}

QJsonObject DataManager::quizToJson(const Quiz& quiz) const {
    QJsonObject obj;
    obj["title"] = QString::fromStdString(quiz.getTitle());
    obj["timeLimit"] = quiz.getTimeLimit();
    obj["difficulty"] = quiz.getDifficulty();
    
    QJsonArray questionsArray;
    for (const Question& question : quiz.getQuestions()) {
        QJsonObject questionObj;
        questionObj["text"] = QString::fromStdString(question.getQuestionText());
        
        QJsonArray choicesArray;
        for (const std::string& choice : question.getChoices()) {
            choicesArray.append(QString::fromStdString(choice));
        }
        questionObj["choices"] = choicesArray;
        questionObj["correctAnswer"] = question.getCorrectAnswer();
        
        questionsArray.append(questionObj);
    }
    obj["questions"] = questionsArray;
    
    return obj;
}

Quiz DataManager::jsonToQuiz(const QJsonObject& json) const {
    std::string title = json["title"].toString().toStdString();
    int timeLimit = json["timeLimit"].toInt();
    int difficulty = json["difficulty"].toInt();
    
    Quiz quiz(title, timeLimit, difficulty);
    
    QJsonArray questionsArray = json["questions"].toArray();
    for (const QJsonValue& value : questionsArray) {
        QJsonObject questionObj = value.toObject();
        std::string text = questionObj["text"].toString().toStdString();
        
        std::array<std::string, 4> choices;
        QJsonArray choicesArray = questionObj["choices"].toArray();
        for (int i = 0; i < 4; ++i) {
            choices[i] = choicesArray[i].toString().toStdString();
        }
        
        int correctAnswer = questionObj["correctAnswer"].toInt();
        quiz.addQuestion(Question(text, choices, correctAnswer));
    }
    
    return quiz;
}

QJsonObject DataManager::scoreToJson(const Score& score) const {
    QJsonObject obj;
    obj["playerId"] = QString::fromStdString(score.getPlayerId());
    obj["quizId"] = QString::fromStdString(score.getQuizId());
    obj["score"] = score.getScore();
    obj["timeTaken"] = score.getTimeTaken();
    obj["timestamp"] = QJsonValue::fromVariant(QDateTime::fromTime_t(
        std::chrono::system_clock::to_time_t(score.getTimestamp())));
    return obj;
}

Score DataManager::jsonToScore(const QJsonObject& json) const {
    std::string playerId = json["playerId"].toString().toStdString();
    std::string quizId = json["quizId"].toString().toStdString();
    double score = json["score"].toDouble();
    int timeTaken = json["timeTaken"].toInt();
    
    return Score(playerId, quizId, score, timeTaken);
}

void DataManager::createSampleData() {
    // Create sample quizzes
    Quiz generalKnowledge("General Knowledge Quiz", 10, 60);
    Quiz scienceQuiz("Science Quiz", 15, 90);
    Quiz historyQuiz("History Quiz", 12, 75);

    // Add questions to General Knowledge Quiz
    generalKnowledge.addQuestion(Question(
        "What is the capital of France?",
        {"London", "Berlin", "Paris", "Madrid"},
        2
    ));
    generalKnowledge.addQuestion(Question(
        "Which planet is known as the Red Planet?",
        {"Venus", "Mars", "Jupiter", "Saturn"},
        1
    ));
    generalKnowledge.addQuestion(Question(
        "What is the largest mammal in the world?",
        {"Elephant", "Blue Whale", "Giraffe", "Hippopotamus"},
        1
    ));

    // Add questions to Science Quiz
    scienceQuiz.addQuestion(Question(
        "What is the chemical symbol for water?",
        {"H2O", "CO2", "O2", "N2"},
        0
    ));
    scienceQuiz.addQuestion(Question(
        "What is the powerhouse of the cell?",
        {"Nucleus", "Mitochondria", "Ribosome", "Golgi Apparatus"},
        1
    ));
    scienceQuiz.addQuestion(Question(
        "What is the speed of light?",
        {"300,000 km/s", "150,000 km/s", "450,000 km/s", "600,000 km/s"},
        0
    ));

    // Add questions to History Quiz
    historyQuiz.addQuestion(Question(
        "Who was the first President of the United States?",
        {"Thomas Jefferson", "George Washington", "Abraham Lincoln", "John Adams"},
        1
    ));
    historyQuiz.addQuestion(Question(
        "In which year did World War II end?",
        {"1943", "1944", "1945", "1946"},
        2
    ));
    historyQuiz.addQuestion(Question(
        "Which ancient civilization built the pyramids?",
        {"Greeks", "Romans", "Egyptians", "Mayans"},
        2
    ));

    // Save the quizzes
    saveQuiz(generalKnowledge);
    saveQuiz(scienceQuiz);
    saveQuiz(historyQuiz);

    // Create a sample admin user
    Admin admin("Admin User", "admin@quiz.com", "admin123");
    saveUser(admin);

    // Create a sample player user
    Player player("Test Player", "player@quiz.com", "player123");
    saveUser(player);

    qDebug() << "Sample data created successfully!";
} 