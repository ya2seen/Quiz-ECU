#ifndef PLAYERDASHBOARD_H
#define PLAYERDASHBOARD_H

#include <QWidget>
#include "Player.h"

namespace Ui {
class PlayerDashboard;
}

class PlayerDashboard : public QWidget {
    Q_OBJECT

public:
    explicit PlayerDashboard(QWidget *parent = nullptr);
    ~PlayerDashboard();

    void setPlayer(Player* player);

signals:
    void logoutRequested();

private slots:
    void onLogoutButtonClicked();
    void onStartQuizButtonClicked();
    void onViewResultsButtonClicked();
    void onViewHistoryButtonClicked();

private:
    Ui::PlayerDashboard *ui;
    Player* player;
    void refreshAvailableQuizzes();
    void refreshScoreHistory();
};

#endif // PLAYERDASHBOARD_H 