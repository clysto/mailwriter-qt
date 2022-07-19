//
// Created by 毛亚琛 on 2022/7/17.
//

#ifndef MAILWRITER_QT_API_H
#define MAILWRITER_QT_API_H

#include <httplib.h>
#include <nlohmann/json.hpp>

class Api {
private:
    httplib::Client cli;
    nlohmann::json auth;

    httplib::Headers getAuthHeaders();

public:
    Api(const std::string &url);

    std::string getUserId(const std::string &name);

    void createMail(std::string to, std::string subject, std::string content);

    void setAuth(nlohmann::json auth);

    void login(const std::string &email, const std::string &password);

    std::string currentUser();

};

#endif //MAILWRITER_QT_API_H
