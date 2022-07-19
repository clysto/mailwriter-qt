//
// Created by 毛亚琛 on 2022/7/19.
//

#include <nlohmann/json.hpp>
#include <httplib.h>
#include <QFile>
#include <QTextStream>
#include "api.h"


Api::Api(const std::string &url)
        : cli(url) {
    auth = false;
}

httplib::Headers Api::getAuthHeaders() {
    return {{"Authorization", "User " + auth["token"].get<std::string>()}};
}

std::string Api::getUserId(const std::string &name) {
    httplib::Params qs = {{"filter", "name= '" + name + "'"}};
    std::string path = httplib::append_query_params("/api/collections/profiles/records", qs);
    auto res = cli.Get(path.c_str(), getAuthHeaders());
    auto data = nlohmann::json::parse(res->body);
    int nums = data["totalItems"].get<int>();
    if (nums == 0) {
        throw "该用户不存在";
    } else {
        return data["items"][0]["id"].get<std::string>();
    }
}

void Api::createMail(std::string to, std::string subject, std::string content) {
    nlohmann::json mail = {
            {"to",      to},
            {"subject", subject},
            {"content", content},
            {"from",    auth["user"]["profile"]["id"].get<std::string>()}
    };
    std::string body = mail.dump();
    httplib::Result res = cli.Post(
            "/api/collections/mails/records",
            getAuthHeaders(),
            body.c_str(),
            body.size(),
            "application/json");
    if (res->status != 200) {
        throw "创建失败";
    }
}

void Api::setAuth(nlohmann::json auth) {
    this->auth = auth;
}

void Api::login(const std::string &email, const std::string &password) {
    nlohmann::json j;
    j["email"] = email;
    j["password"] = password;
    std::string body = j.dump();
    httplib::Result res = cli.Post(
            "/api/users/auth-via-email",
            body.c_str(),
            body.size(),
            "application/json");

    if (res->status == 200) {
        auth = nlohmann::json::parse(res->body);
        QFile f("session.json");
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&f);
        out << res->body.c_str();
        f.close();
    } else {
        throw "登录失败";
    }
}

std::string Api::currentUser() {
    return auth["user"]["profile"]["name"].get<std::string>();
}
