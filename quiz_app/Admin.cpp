#include "Admin.h"
#include <algorithm>
#include <stdexcept>

Admin::Admin(const std::string& name, const std::string& email, const std::string& password)
    : User(name, email, password) {}

std::string Admin::getUserType() const {
    return "Admin";
}

void Admin::createQuiz(const Quiz& quiz) {
    quizzes.push_back(quiz);
}

void Admin::deleteQuiz(const std::string& quizId) {
    auto it = std::find_if(quizzes.begin(), quizzes.end(),
        [&quizId](const Quiz& q) { return q.getTitle() == quizId; });
    
    if (it != quizzes.end()) {
        quizzes.erase(it);
    } else {
        throw std::runtime_error("Quiz not found");
    }
}

Quiz& Admin::getQuiz(const std::string& quizId) {
    auto it = std::find_if(quizzes.begin(), quizzes.end(),
        [&quizId](const Quiz& q) { return q.getTitle() == quizId; });
    
    if (it != quizzes.end()) {
        return *it;
    }
    throw std::runtime_error("Quiz not found");
}

void Admin::addQuestionToQuiz(const std::string& quizId, const Question& question) {
    Quiz& quiz = getQuiz(quizId);
    quiz.addQuestion(question);
}

void Admin::editQuestionInQuiz(const std::string& quizId, int questionIndex, const Question& question) {
    Quiz& quiz = getQuiz(quizId);
    quiz.editQuestion(questionIndex, question);
}

void Admin::deleteQuestionFromQuiz(const std::string& quizId, int questionIndex) {
    Quiz& quiz = getQuiz(quizId);
    quiz.removeQuestion(questionIndex);
}

const std::vector<Quiz>& Admin::getAllQuizzes() const {
    return quizzes;
} 