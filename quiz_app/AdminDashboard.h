#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QWidget>
#include "Admin.h"

namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QWidget {
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();

    void setAdmin(Admin* admin);

signals:
    void logoutRequested();

private slots:
    void onLogoutButtonClicked();
    void onCreateQuizButtonClicked();
    void onEditQuizButtonClicked();
    void onDeleteQuizButtonClicked();
    void onAddQuestionButtonClicked();
    void onEditQuestionButtonClicked();
    void onDeleteQuestionButtonClicked();
    void onViewResultsButtonClicked();

private:
    Ui::AdminDashboard *ui;
    Admin* admin;
    void refreshQuizList();
    void refreshQuestionList();
};

#endif // ADMINDASHBOARD_H 