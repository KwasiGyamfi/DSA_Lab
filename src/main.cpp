#include "student.hpp"
#include "instructor.hpp"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main()
{
    try
    {
        vector<unique_ptr<Person>> people;

        people.emplace_back(
            make_unique<Student>(
                1,
                "Ada",
                "ada@uni.edu",
                2026,
                vector<string>{"CS101", "MATH200"}
            )
        );

        people.emplace_back(
            make_unique<Instructor>(
                2,
                "Grace",
                "grace@uni.edu",
                "Room 314",
                vector<string>{"CS101"}
            )
        );

        nlohmann::json j = nlohmann::json::array();

        for (const auto& p : people)
        {
            j.push_back(p->to_json());
        }

        cout << "JSON:\n";
        cout << j.dump(2) << "\n\n";

        YAML::Node y;

        for (const auto& p : people)
        {
            y.push_back(p->to_yaml());
        }

        cout << "YAML:\n";
        cout << YAML::Dump(y) << "\n";

        cout << "\nCSV (Student):\n";

        Student tmpS(99, "Tmp", "tmp@uni.edu", 2030);

        cout << tmpS.csv_header() << "\n";
        cout << static_cast<Student&>(*people[0]).csv_row() << "\n";

        cout << "\nCSV (Instructor):\n";

        Instructor tmpI(98, "TmpI", "tmpI@uni.edu", "Room 1");

        cout << tmpI.csv_header() << "\n";
        cout << static_cast<Instructor&>(*people[1]).csv_row() << "\n";
    }

    catch (const ValidationError& e)
    {
        cerr << "ValidationError: " << e.what() << "\n";
        return 2;
    }

    catch (const SerializationError& e)
    {
        cerr << "SerializationError: " << e.what() << "\n";
        return 3;
    }

    catch (const exception& e)
    {
        cerr << "Unhandled std::exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}