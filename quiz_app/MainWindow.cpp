#include "MainWindow.h"
#include "LoginPage.h"
#include "RegistrationPage.h"
#include "AdminDashboard.h"
#include "PlayerDashboard.h"
#include "DataManager.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stackedWidget(new QStackedWidget(this))
{
    ui->setupUi(this);
    setCentralWidget(stackedWidget);
    
    // Create and add pages
    LoginPage *loginPage = new LoginPage(this);
    RegistrationPage *registrationPage = new RegistrationPage(this);
    AdminDashboard *adminDashboard = new AdminDashboard(this);
    PlayerDashboard *playerDashboard = new PlayerDashboard(this);
    
    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(registrationPage);
    stackedWidget->addWidget(adminDashboard);
    stackedWidget->addWidget(playerDashboard);
    
    setupConnections();
    showLoginPage();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupConnections() {
    // Connect login page signals
    LoginPage *loginPage = qobject_cast<LoginPage*>(stackedWidget->widget(0));
    connect(loginPage, &LoginPage::loginRequested, this, &MainWindow::handleLogin);
    connect(loginPage, &LoginPage::registrationRequested, this, &MainWindow::showRegistrationPage);
    
    // Connect registration page signals
    RegistrationPage *registrationPage = qobject_cast<RegistrationPage*>(stackedWidget->widget(1));
    connect(registrationPage, &RegistrationPage::registrationRequested, this, &MainWindow::handleRegistration);
    connect(registrationPage, &RegistrationPage::backToLoginRequested, this, &MainWindow::showLoginPage);
    
    // Connect admin dashboard signals
    AdminDashboard *adminDashboard = qobject_cast<AdminDashboard*>(stackedWidget->widget(2));
    connect(adminDashboard, &AdminDashboard::logoutRequested, this, &MainWindow::handleLogout);
    
    // Connect player dashboard signals
    PlayerDashboard *playerDashboard = qobject_cast<PlayerDashboard*>(stackedWidget->widget(3));
    connect(playerDashboard, &PlayerDashboard::logoutRequested, this, &MainWindow::handleLogout);
}

void MainWindow::showLoginPage() {
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::showRegistrationPage() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showAdminDashboard() {
    AdminDashboard *adminDashboard = qobject_cast<AdminDashboard*>(stackedWidget->widget(2));
    adminDashboard->setAdmin(dynamic_cast<Admin*>(currentUser.get()));
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::showPlayerDashboard() {
    PlayerDashboard *playerDashboard = qobject_cast<PlayerDashboard*>(stackedWidget->widget(3));
    playerDashboard->setPlayer(dynamic_cast<Player*>(currentUser.get()));
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::handleLogin(const QString& email, const QString& password) {
    auto user = DataManager::getInstance().loadUser(email);
    if (user && user->authenticate(password.toStdString())) {
        currentUser = std::move(user);
        if (currentUser->getUserType() == "Admin") {
            showAdminDashboard();
        } else {
            showPlayerDashboard();
        }
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid email or password.");
    }
}

void MainWindow::handleRegistration(const QString& name, const QString& email, 
                                  const QString& password, bool isAdmin) {
    if (DataManager::getInstance().userExists(email)) {
        QMessageBox::warning(this, "Registration Failed", "Email already exists.");
        return;
    }
    
    std::unique_ptr<User> newUser;
    if (isAdmin) {
        newUser = std::make_unique<Admin>(name.toStdString(), email.toStdString(), password.toStdString());
    } else {
        newUser = std::make_unique<Player>(name.toStdString(), email.toStdString(), password.toStdString());
    }
    
    DataManager::getInstance().saveUser(*newUser);
    QMessageBox::information(this, "Registration Successful", "Account created successfully.");
    showLoginPage();
}

void MainWindow::handleLogout() {
    clearCurrentUser();
    showLoginPage();
}

void MainWindow::clearCurrentUser() {
    currentUser.reset();
} 