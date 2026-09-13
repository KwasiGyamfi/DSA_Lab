#pragma once

#include "person.hpp"
#include "csv.hpp"
#include <vector>

using namespace std;

class Student : public Person
{
    int grad_year_;
    vector<string> courses_;

public:
   Student(int id, string name, string email, int grad_year,
        vector<string> courses = {})
    : Person(id, name, email),
      grad_year_(grad_year)
{
    if (grad_year < 2000)
    {
        throw ValidationError("grad_year too small");
    }

    courses_ = move(courses);
}

    string role() const override
    {
        return "Student";
    }

static Student from_json(const nlohmann::json& j)
{
    try
    {
        if (!j.contains("id") ||
            !j.contains("name") ||
            !j.contains("email") ||
            !j.contains("grad_year"))
        {
            throw ValidationError("Missing required Student field");
        }

        return Student(
            j.at("id").get<int>(),
            j.at("name").get<string>(),
            j.at("email").get<string>(),
            j.at("grad_year").get<int>(),
            j.value("courses", vector<string>{})
        );
    }
    catch (const ValidationError&)
    {
        throw;
    }
    catch (const exception& e)
    {
        throw ValidationError(
            string("Invalid Student JSON: ") + e.what()
        );
    }
}

    nlohmann::json to_json() const override
    {
        return {
            {"role", role()},
            {"id", id_},
            {"name", name_},
            {"email", email_},
            {"grad_year", grad_year_},
            {"courses", courses_}
        };
    }

    YAML::Node to_yaml() const override
    {
        YAML::Node n;

        n["role"] = role();
        n["id"] = id_;
        n["name"] = name_;
        n["email"] = email_;
        n["grad_year"] = grad_year_;

        for (const auto& c : courses_)
        {
            n["courses"].push_back(c);
        }

        return n;
    }

    string csv_header() const override
    {
        return "role,id,name,email,grad_year,courses";
    }

    string csv_row() const override
    {
        string joined;

        for (size_t i = 0; i < courses_.size(); ++i)
        {
            if (i)
            {
                joined += ';';
            }

            joined += courses_[i];
        }

        return csv_escape(role()) + "," +
               to_string(id_) + "," +
               csv_escape(name_) + "," +
               csv_escape(email_) + "," +
               to_string(grad_year_) + "," +
               csv_escape(joined);
    }
};