#ifndef PLAYER_H
#define PLAYER_H

#include "User.h"
#include "Quiz.h"
#include "Score.h"
#include <vector>

class Player : public User {
private:
    std::vector<Score> scores;

public:
    Player(const std::string& name, const std::string& email, const std::string& password);
    
    // Override base class method
    std::string getUserType() const override;
    
    // Quiz taking functionality
    Score takeQuiz(const Quiz& quiz, const std::vector<int>& answers, int timeTaken);
    
    // Score management
    const std::vector<Score>& getScores() const;
    double getAverageScore() const;
    double getHighestScore() const;
    
    // Quiz history
    std::vector<std::string> getCompletedQuizzes() const;
};

#endif // PLAYER_H 