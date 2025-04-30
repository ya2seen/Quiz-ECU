#include "LoginPage.h"
#include "ui_LoginPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    
    // Create layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(40, 40, 40, 40);
    
    // Create title
    QLabel *titleLabel = new QLabel("Quiz Application", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2e7d32;");
    layout->addWidget(titleLabel);
    
    // Create form
    QWidget *formWidget = new QWidget(this);
    QVBoxLayout *formLayout = new QVBoxLayout(formWidget);
    formLayout->setSpacing(15);
    
    // Email input
    QLabel *emailLabel = new QLabel("Email:", this);
    QLineEdit *emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Enter your email");
    formLayout->addWidget(emailLabel);
    formLayout->addWidget(emailEdit);
    
    // Password input
    QLabel *passwordLabel = new QLabel("Password:", this);
    QLineEdit *passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Enter your password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    formLayout->addWidget(passwordLabel);
    formLayout->addWidget(passwordEdit);
    
    // Login button
    QPushButton *loginButton = new QPushButton("Login", this);
    loginButton->setMinimumHeight(40);
    formLayout->addWidget(loginButton);
    
    // Register button
    QPushButton *registerButton = new QPushButton("Create New Account", this);
    registerButton->setStyleSheet("background-color: #2196F3;");
    registerButton->setMinimumHeight(40);
    formLayout->addWidget(registerButton);
    
    layout->addWidget(formWidget);
    setLayout(layout);
    
    // Connect signals
    connect(loginButton, &QPushButton::clicked, this, [this, emailEdit, passwordEdit]() {
        if (emailEdit->text().isEmpty() || passwordEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill in all fields.");
            return;
        }
        emit loginRequested(emailEdit->text(), passwordEdit->text());
    });
    
    connect(registerButton, &QPushButton::clicked, this, &LoginPage::registrationRequested);
}

LoginPage::~LoginPage() {
    delete ui;
}

void LoginPage::onLoginButtonClicked() {
    emit loginRequested(ui->emailEdit->text(), ui->passwordEdit->text());
}

void LoginPage::onRegisterButtonClicked() {
    emit registrationRequested();
} 