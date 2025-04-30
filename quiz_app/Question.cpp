#include "Question.h"

Question::Question(const std::string& text, 
                  const std::array<std::string, 4>& choices,
                  int correctAnswer)
    : questionText(text), choices(choices), correctAnswer(correctAnswer) {
    if (correctAnswer < 0 || correctAnswer > 3) {
        throw std::invalid_argument("Correct answer must be between 0 and 3");
    }
}

std::string Question::getQuestionText() const {
    return questionText;
}

std::array<std::string, 4> Question::getChoices() const {
    return choices;
}

int Question::getCorrectAnswer() const {
    return correctAnswer;
}

bool Question::isCorrect(int answer) const {
    return answer == correctAnswer;
}

std::string Question::getCorrectAnswerText() const {
    return choices[correctAnswer];
} 