#pragma once

#include "serializable.hpp"
#include "exceptions.hpp"
#include <string>
#include <regex>

using namespace std;

class Person : public Serializable
{
protected:
    int id_;
    string name_;
    string email_;

    static void validate_email(const string& e)
    {
        static const regex re(R"(^[^@\s]+@[^@\s]+\.[^@\s]+$)");

        if (!regex_match(e, re))
        {
            throw ValidationError("Invalid email: " + e);
        }
    }

public:
   Person(int id, string name, string email)
    : id_(id)
{
    if (id <= 0)
    {
        throw ValidationError("id must be positive");
    }

    if (name.empty())
    {
        throw ValidationError("name is required");
    }

    validate_email(email);

    name_ = move(name);
    email_ = move(email);
}

    virtual string role() const = 0;

    int id() const
    {
        return id_;
    }

    const string& name() const
    {
        return name_;
    }

    const string& email() const
    {
        return email_;
    }
};