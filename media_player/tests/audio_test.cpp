#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::Music music;

    if (!music.openFromFile("assets/song1.mp3"))
    {
        cerr << "FAIL: Could not load MP3." << endl;
        return 1;
    }

    cout << "PASS: MP3 loaded successfully." << endl;
    cout << "Duration: "
         << music.getDuration().asSeconds()
         << " seconds" << endl;

    return 0;
}