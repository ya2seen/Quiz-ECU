#ifndef QUIZ_H
#define QUIZ_H

#include "Question.h"
#include <vector>
#include <string>
#include <chrono>

class Quiz {
private:
    std::string title;
    std::vector<Question> questions;
    int timeLimit; // in seconds
    int difficulty; // 1-3 (easy, medium, hard)

public:
    Quiz(const std::string& title, int timeLimit = 0, int difficulty = 1);
    
    // Question management
    void addQuestion(const Question& question);
    void removeQuestion(int index);
    void editQuestion(int index, const Question& question);
    
    // Getters
    std::string getTitle() const;
    int getTimeLimit() const;
    int getDifficulty() const;
    int getQuestionCount() const;
    const std::vector<Question>& getQuestions() const;
    
    // Quiz operations
    double calculateScore(const std::vector<int>& answers) const;
    std::chrono::seconds getRemainingTime() const;
    
private:
    std::chrono::steady_clock::time_point startTime;
};

#endif // QUIZ_H 