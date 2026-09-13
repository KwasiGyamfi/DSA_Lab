# C++ Inheritance & Serialization Lab

## Design Choices

This project uses an abstract `Person` base class with two derived classes: `Student` and `Instructor`.

`Person` stores information shared by both derived classes, including an ID, name, and email address. `Student` adds a graduation year and a list of courses, while `Instructor` adds an office and a list of courses taught.

The `Serializable` interface requires each concrete class to provide JSON, YAML, and CSV serialization functions. Polymorphism allows `Student` and `Instructor` objects to be accessed through `Person` pointers while still calling the correct overridden serialization methods.

The project uses CMake to organize the build and FetchContent to provide nlohmann/json, yaml-cpp, and Catch2.

## Exceptions and Validation

The project defines two custom exception types:

* `ValidationError`
* `SerializationError`

`ValidationError` is thrown when object data is invalid. Examples include:

* an ID that is not positive
* an empty name
* an invalid email address
* a graduation year below 2000
* an empty instructor office
* missing or invalid fields while parsing JSON

Validation occurs before values are moved into the object's final state where possible to improve exception safety.

## CSV Escaping

The `csv_escape` helper function checks whether a CSV field contains a comma, quotation mark, or newline.

If one of these characters is found, the field is surrounded by quotation marks. Any quotation marks already inside the value are doubled.

For example:

`Eve, "The Great"`

becomes:

`"Eve, ""The Great"""`

This prevents commas and quotation marks inside a value from being interpreted incorrectly as CSV separators.

## Challenge Extensions

This implementation includes:

1. JSON round-trip parsing using `Student::from_json()` and `Instructor::from_json()`, including validation of missing or invalid data.
2. Stronger exception safety by validating data before moving values into object state where possible.

Catch2 tests verify serialization, validation, CSV escaping, and JSON round-trip behavior.
