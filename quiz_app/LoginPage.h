#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget {
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

signals:
    void loginRequested(const QString& email, const QString& password);
    void registrationRequested();

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();

private:
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H 