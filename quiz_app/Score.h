#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <chrono>

class Score {
private:
    std::string playerId;
    std::string quizId;
    double score;
    std::chrono::system_clock::time_point timestamp;
    int timeTaken; // in seconds

public:
    Score(const std::string& playerId, 
          const std::string& quizId, 
          double score,
          int timeTaken);

    // Getters
    std::string getPlayerId() const;
    std::string getQuizId() const;
    double getScore() const;
    std::chrono::system_clock::time_point getTimestamp() const;
    int getTimeTaken() const;

    // String representation
    std::string toString() const;
};

#endif // SCORE_H 