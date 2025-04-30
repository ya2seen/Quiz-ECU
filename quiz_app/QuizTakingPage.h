#ifndef QUIZTAKINGPAGE_H
#define QUIZTAKINGPAGE_H

#include <QWidget>
#include "Quiz.h"
#include "Player.h"

namespace Ui {
class QuizTakingPage;
}

class QuizTakingPage : public QWidget {
    Q_OBJECT

public:
    explicit QuizTakingPage(QWidget *parent = nullptr);
    ~QuizTakingPage();

    void startQuiz(const Quiz& quiz, Player* player);

signals:
    void quizCompleted();
    void backToDashboard();

private slots:
    void onNextButtonClicked();
    void onPreviousButtonClicked();
    void onSubmitButtonClicked();
    void onBackButtonClicked();
    void updateTimer();

private:
    Ui::QuizTakingPage *ui;
    Quiz currentQuiz;
    Player* currentPlayer;
    std::vector<int> answers;
    int currentQuestionIndex;
    QTimer* timer;
    int timeRemaining;

    void displayQuestion(int index);
    void saveAnswer();
    void calculateAndSaveScore();
    void updateProgress();
};

#endif // QUIZTAKINGPAGE_H 