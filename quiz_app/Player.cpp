#include "Player.h"
#include <algorithm>
#include <numeric>

Player::Player(const std::string& name, const std::string& email, const std::string& password)
    : User(name, email, password) {}

std::string Player::getUserType() const {
    return "Player";
}

Score Player::takeQuiz(const Quiz& quiz, const std::vector<int>& answers, int timeTaken) {
    double score = quiz.calculateScore(answers);
    Score newScore(getEmail(), quiz.getTitle(), score, timeTaken);
    scores.push_back(newScore);
    return newScore;
}

const std::vector<Score>& Player::getScores() const {
    return scores;
}

double Player::getAverageScore() const {
    if (scores.empty()) {
        return 0.0;
    }
    
    double sum = std::accumulate(scores.begin(), scores.end(), 0.0,
        [](double acc, const Score& s) { return acc + s.getScore(); });
    
    return sum / scores.size();
}

double Player::getHighestScore() const {
    if (scores.empty()) {
        return 0.0;
    }
    
    return std::max_element(scores.begin(), scores.end(),
        [](const Score& a, const Score& b) { return a.getScore() < b.getScore(); })->getScore();
}

std::vector<std::string> Player::getCompletedQuizzes() const {
    std::vector<std::string> completedQuizzes;
    for (const auto& score : scores) {
        completedQuizzes.push_back(score.getQuizId());
    }
    return completedQuizzes;
} 