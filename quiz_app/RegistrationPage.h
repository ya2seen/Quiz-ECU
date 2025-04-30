#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include <QWidget>

namespace Ui {
class RegistrationPage;
}

class RegistrationPage : public QWidget {
    Q_OBJECT

public:
    explicit RegistrationPage(QWidget *parent = nullptr);
    ~RegistrationPage();

signals:
    void registrationRequested(const QString& name, const QString& email, 
                             const QString& password, bool isAdmin);
    void backToLoginRequested();

private slots:
    void onRegisterButtonClicked();
    void onBackButtonClicked();

private:
    Ui::RegistrationPage *ui;
    bool validateInput();
};

#endif // REGISTRATIONPAGE_H 