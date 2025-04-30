#include "RegistrationPage.h"
#include "ui_RegistrationPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>

RegistrationPage::RegistrationPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegistrationPage)
{
    ui->setupUi(this);
    
    // Create layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(40, 40, 40, 40);
    
    // Create title
    QLabel *titleLabel = new QLabel("Create New Account", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2e7d32;");
    layout->addWidget(titleLabel);
    
    // Create form
    QWidget *formWidget = new QWidget(this);
    QVBoxLayout *formLayout = new QVBoxLayout(formWidget);
    formLayout->setSpacing(15);
    
    // Name input
    QLabel *nameLabel = new QLabel("Name:", this);
    QLineEdit *nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Enter your name");
    formLayout->addWidget(nameLabel);
    formLayout->addWidget(nameEdit);
    
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
    
    // User type selection
    QLabel *typeLabel = new QLabel("Account Type:", this);
    QWidget *typeWidget = new QWidget(this);
    QHBoxLayout *typeLayout = new QHBoxLayout(typeWidget);
    typeLayout->setSpacing(20);
    
    QRadioButton *playerRadio = new QRadioButton("Player", this);
    QRadioButton *adminRadio = new QRadioButton("Admin", this);
    playerRadio->setChecked(true);
    
    typeLayout->addWidget(playerRadio);
    typeLayout->addWidget(adminRadio);
    typeLayout->addStretch();
    
    formLayout->addWidget(typeLabel);
    formLayout->addWidget(typeWidget);
    
    // Register button
    QPushButton *registerButton = new QPushButton("Register", this);
    registerButton->setMinimumHeight(40);
    formLayout->addWidget(registerButton);
    
    // Back button
    QPushButton *backButton = new QPushButton("Back to Login", this);
    backButton->setStyleSheet("background-color: #2196F3;");
    backButton->setMinimumHeight(40);
    formLayout->addWidget(backButton);
    
    layout->addWidget(formWidget);
    setLayout(layout);
    
    // Connect signals
    connect(registerButton, &QPushButton::clicked, this, [this, nameEdit, emailEdit, passwordEdit, adminRadio]() {
        if (!validateInput()) {
            return;
        }
        emit registrationRequested(nameEdit->text(), emailEdit->text(), 
                                passwordEdit->text(), adminRadio->isChecked());
    });
    
    connect(backButton, &QPushButton::clicked, this, &RegistrationPage::backToLoginRequested);
}

RegistrationPage::~RegistrationPage() {
    delete ui;
}

bool RegistrationPage::validateInput() {
    if (ui->nameEdit->text().isEmpty() || 
        ui->emailEdit->text().isEmpty() || 
        ui->passwordEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all fields.");
        return false;
    }
    
    if (ui->passwordEdit->text().length() < 6) {
        QMessageBox::warning(this, "Error", "Password must be at least 6 characters long.");
        return false;
    }
    
    return true;
}

void RegistrationPage::onRegisterButtonClicked() {
    if (!validateInput()) {
        return;
    }
    emit registrationRequested(ui->nameEdit->text(), ui->emailEdit->text(), 
                            ui->passwordEdit->text(), ui->adminRadio->isChecked());
}

void RegistrationPage::onBackButtonClicked() {
    emit backToLoginRequested();
} 