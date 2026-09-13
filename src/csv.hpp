#pragma once

#include <string>
#include <algorithm>

using namespace std;

inline string csv_escape(string s)
{
    bool need_quotes = s.find_first_of(",\"\n") != string::npos;

    if (need_quotes)
    {
        string t;
        t.reserve(s.size() + 2);

        for (char c : s)
        {
            t += (c == '"') ? string("\"\"") : string(1, c);
        }

        return "\"" + t + "\"";
    }

    return s;
}