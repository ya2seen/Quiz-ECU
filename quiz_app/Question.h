#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <array>

class Question {
private:
    std::string questionText;
    std::array<std::string, 4> choices;
    int correctAnswer; // Index of the correct answer (0-3)

public:
    Question(const std::string& text, 
             const std::array<std::string, 4>& choices,
             int correctAnswer);

    // Getters
    std::string getQuestionText() const;
    std::array<std::string, 4> getChoices() const;
    int getCorrectAnswer() const;

    // Validation
    bool isCorrect(int answer) const;
    std::string getCorrectAnswerText() const;
};

#endif // QUESTION_H 