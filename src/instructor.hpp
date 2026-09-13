#pragma once

#include "person.hpp"
#include "csv.hpp"
#include <vector>

using namespace std;

class Instructor : public Person
{
    string office_;
    vector<string> teaches_;

public:
   Instructor(int id, string name, string email,
           string office, vector<string> teaches = {})
    : Person(id, name, email)
{
    if (office.empty())
    {
        throw ValidationError("office is required");
    }

    office_ = move(office);
    teaches_ = move(teaches);
}

    string role() const override
    {
        return "Instructor";
    }

static Instructor from_json(const nlohmann::json& j)
{
    try
    {
        if (!j.contains("id") ||
            !j.contains("name") ||
            !j.contains("email") ||
            !j.contains("office"))
        {
            throw ValidationError("Missing required Instructor field");
        }

        return Instructor(
            j.at("id").get<int>(),
            j.at("name").get<string>(),
            j.at("email").get<string>(),
            j.at("office").get<string>(),
            j.value("teaches", vector<string>{})
        );
    }
    catch (const ValidationError&)
    {
        throw;
    }
    catch (const exception& e)
    {
        throw ValidationError(
            string("Invalid Instructor JSON: ") + e.what()
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
            {"office", office_},
            {"teaches", teaches_}
        };
    }

    YAML::Node to_yaml() const override
    {
        YAML::Node n;

        n["role"] = role();
        n["id"] = id_;
        n["name"] = name_;
        n["email"] = email_;
        n["office"] = office_;

        for (const auto& c : teaches_)
        {
            n["teaches"].push_back(c);
        }

        return n;
    }

    string csv_header() const override
    {
        return "role,id,name,email,office,teaches";
    }

    string csv_row() const override
    {
        string joined;

        for (size_t i = 0; i < teaches_.size(); ++i)
        {
            if (i)
            {
                joined += ';';
            }

            joined += teaches_[i];
        }

        return csv_escape(role()) + "," +
               to_string(id_) + "," +
               csv_escape(name_) + "," +
               csv_escape(email_) + "," +
               csv_escape(office_) + "," +
               csv_escape(joined);
    }
};