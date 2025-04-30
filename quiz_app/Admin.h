#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Question.h"
#include "Quiz.h"
#include <vector>

class Admin : public User {
private:
    std::vector<Quiz> quizzes;

public:
    Admin(const std::string& name, const std::string& email, const std::string& password);
    
    // Override base class method
    std::string getUserType() const override;
    
    // Quiz management
    void createQuiz(const Quiz& quiz);
    void deleteQuiz(const std::string& quizId);
    Quiz& getQuiz(const std::string& quizId);
    
    // Question management
    void addQuestionToQuiz(const std::string& quizId, const Question& question);
    void editQuestionInQuiz(const std::string& quizId, int questionIndex, const Question& question);
    void deleteQuestionFromQuiz(const std::string& quizId, int questionIndex);
    
    // Get all quizzes
    const std::vector<Quiz>& getAllQuizzes() const;
};

#endif // ADMIN_H 