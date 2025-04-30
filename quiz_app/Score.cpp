#include "Score.h"
#include <sstream>
#include <iomanip>
#include <ctime>

Score::Score(const std::string& playerId, 
             const std::string& quizId, 
             double score,
             int timeTaken)
    : playerId(playerId), 
      quizId(quizId), 
      score(score), 
      timestamp(std::chrono::system_clock::now()),
      timeTaken(timeTaken) {
    if (score < 0 || score > 100) {
        throw std::invalid_argument("Score must be between 0 and 100");
    }
}

std::string Score::getPlayerId() const {
    return playerId;
}

std::string Score::getQuizId() const {
    return quizId;
}

double Score::getScore() const {
    return score;
}

std::chrono::system_clock::time_point Score::getTimestamp() const {
    return timestamp;
}

int Score::getTimeTaken() const {
    return timeTaken;
}

std::string Score::toString() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
    std::tm* tm = std::localtime(&time);
    
    std::stringstream ss;
    ss << "Player: " << playerId << "\n"
       << "Quiz: " << quizId << "\n"
       << "Score: " << std::fixed << std::setprecision(2) << score << "%\n"
       << "Time Taken: " << timeTaken << " seconds\n"
       << "Date: " << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    
    return ss.str();
} 