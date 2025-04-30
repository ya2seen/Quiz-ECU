#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
protected:
    std::string name;
    std::string email;
    std::string password; // Will be encrypted

public:
    User(const std::string& name, const std::string& email, const std::string& password);
    virtual ~User() = default;

    // Getters
    std::string getName() const;
    std::string getEmail() const;

    // Authentication methods
    bool authenticate(const std::string& inputPassword) const;
    void changePassword(const std::string& newPassword);

    // Virtual methods for derived classes
    virtual std::string getUserType() const = 0;

private:
    // Helper method for password encryption/decryption
    std::string encryptDecrypt(const std::string& input) const;
};

#endif // USER_H 