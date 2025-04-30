#include "Quiz.h"
#include <stdexcept>

Quiz::Quiz(const std::string& title, int timeLimit, int difficulty)
    : title(title), timeLimit(timeLimit), difficulty(difficulty) {
    if (difficulty < 1 || difficulty > 3) {
        throw std::invalid_argument("Difficulty must be between 1 and 3");
    }
    startTime = std::chrono::steady_clock::now();
}

void Quiz::addQuestion(const Question& question) {
    questions.push_back(question);
}

void Quiz::removeQuestion(int index) {
    if (index < 0 || index >= questions.size()) {
        throw std::out_of_range("Invalid question index");
    }
    questions.erase(questions.begin() + index);
}

void Quiz::editQuestion(int index, const Question& question) {
    if (index < 0 || index >= questions.size()) {
        throw std::out_of_range("Invalid question index");
    }
    questions[index] = question;
}

std::string Quiz::getTitle() const {
    return title;
}

int Quiz::getTimeLimit() const {
    return timeLimit;
}

int Quiz::getDifficulty() const {
    return difficulty;
}

int Quiz::getQuestionCount() const {
    return questions.size();
}

const std::vector<Question>& Quiz::getQuestions() const {
    return questions;
}

double Quiz::calculateScore(const std::vector<int>& answers) const {
    if (answers.size() != questions.size()) {
        throw std::invalid_argument("Number of answers must match number of questions");
    }

    int correct = 0;
    for (size_t i = 0; i < questions.size(); ++i) {
        if (questions[i].isCorrect(answers[i])) {
            correct++;
        }
    }

    return (static_cast<double>(correct) / questions.size()) * 100.0;
}

std::chrono::seconds Quiz::getRemainingTime() const {
    if (timeLimit == 0) {
        return std::chrono::seconds(0);
    }

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
    auto remaining = std::chrono::seconds(timeLimit) - elapsed;

    return remaining > std::chrono::seconds(0) ? remaining : std::chrono::seconds(0);
} 