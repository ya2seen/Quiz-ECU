#include "User.h"
#include <algorithm>

User::User(const std::string& name, const std::string& email, const std::string& password)
    : name(name), email(email), password(encryptDecrypt(password)) {}

std::string User::getName() const {
    return name;
}

std::string User::getEmail() const {
    return email;
}

bool User::authenticate(const std::string& inputPassword) const {
    return encryptDecrypt(inputPassword) == password;
}

void User::changePassword(const std::string& newPassword) {
    password = encryptDecrypt(newPassword);
}

std::string User::encryptDecrypt(const std::string& input) const {
    // Simple XOR encryption with a fixed key
    const char key = 'K'; // This is a simple key, in a real app use a more secure method
    std::string output = input;
    
    for (size_t i = 0; i < input.length(); ++i) {
        output[i] = input[i] ^ key;
    }
    
    return output;
} 