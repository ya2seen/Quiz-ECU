#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "User.h"
#include "Admin.h"
#include "Player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showLoginPage();
    void showRegistrationPage();
    void showAdminDashboard();
    void showPlayerDashboard();
    void handleLogin();
    void handleRegistration();
    void handleLogout();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    std::unique_ptr<User> currentUser;
    
    void setupConnections();
    void loadUserData();
    void saveUserData();
    void clearCurrentUser();
};

#endif // MAINWINDOW_H 