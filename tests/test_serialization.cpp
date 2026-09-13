#include <catch2/catch_test_macros.hpp>
#include "student.hpp"
#include "instructor.hpp"

using namespace std;

TEST_CASE("Student JSON serialization")
{
    Student s(
        10,
        "Alice",
        "alice@uni.edu",
        2027,
        {"CS101", "HIST110"}
    );

    auto j = s.to_json();

    CHECK(j.at("role") == "Student");
    CHECK(j.at("name") == "Alice");
    CHECK(j.at("grad_year") == 2027);
}

TEST_CASE("Instructor YAML serialization")
{
    Instructor i(
        11,
        "Bob",
        "bob@uni.edu",
        "C-210",
        {"CS101"}
    );

    auto y = i.to_yaml();

    CHECK(y["role"].as<string>() == "Instructor");
    CHECK(y["office"].as<string>() == "C-210");
}

TEST_CASE("CSV escaping handles commas and quotes")
{
    Student s(
        12,
        "Eve, \"The Great\"",
        "eve@uni.edu",
        2028,
        {"CS,101", "AI\"Lab"}
    );

    auto row = s.csv_row();

    REQUIRE(
        row.find("\"Eve, \"\"The Great\"\"\"") != string::npos
    );
}

TEST_CASE("Validation throws on bad email")
{
    REQUIRE_THROWS_AS(
        Student(
            13,
            "Zed",
            "not-an-email",
            2026
        ),
        ValidationError
    );
}

TEST_CASE("Student JSON round-trip")
{
    Student original(
        20,
        "Maya",
        "maya@uni.edu",
        2029,
        {"CS201", "MATH250"}
    );

    auto j = original.to_json();
    Student restored = Student::from_json(j);

    CHECK(restored.id() == original.id());
    CHECK(restored.name() == original.name());
    CHECK(restored.email() == original.email());
    CHECK(restored.role() == original.role());
}

TEST_CASE("Invalid Student JSON throws ValidationError")
{
    nlohmann::json bad = {
        {"name", "Missing Id"},
        {"email", "valid@uni.edu"},
        {"grad_year", 2027}
    };

    REQUIRE_THROWS_AS(
        Student::from_json(bad),
        ValidationError
    );
}

TEST_CASE("Instructor JSON round-trip")
{
    Instructor original(
        21,
        "Jordan",
        "jordan@uni.edu",
        "B-120",
        {"CS301", "CS450"}
    );

    auto j = original.to_json();
    Instructor restored = Instructor::from_json(j);

    CHECK(restored.id() == original.id());
    CHECK(restored.name() == original.name());
    CHECK(restored.email() == original.email());
    CHECK(restored.role() == original.role());
}

TEST_CASE("Invalid Instructor JSON throws ValidationError")
{
    nlohmann::json bad = {
        {"id", 22},
        {"name", "Professor X"},
        {"email", "prof@uni.edu"}
    };

    REQUIRE_THROWS_AS(
        Instructor::from_json(bad),
        ValidationError
    );
}

