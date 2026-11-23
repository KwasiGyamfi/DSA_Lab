
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Playlist.h"

using namespace std;

int main()
{
    Playlist playlist;

    // Replace these paths with actual audio files later.
    playlist.addSong(Song("Song Three", "Artist C", 190,
                          "assets/song3.mp3"));
    playlist.addSong(Song("Song Two", "Artist B", 210,
                          "assets/song2.mp3"));
    playlist.addSong(Song("Song One", "Artist A", 180,
                          "assets/song1.mp3"));

    sf::RenderWindow window(
        sf::VideoMode(760, 550),
        "SFML Linked List Media Player"
    );

    window.setFramerateLimit(60);

    sf::Font font;

    if (!font.loadFromFile(
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
    {
        cerr << "Could not load font." << endl;
        return 1;
    }

    sf::Music music;
    bool isPlaying = false;

    sf::Text heading("LINKED LIST MEDIA PLAYER", font, 23);
    heading.setPosition(40, 25);
    heading.setFillColor(sf::Color::White);

    sf::Text nowPlaying("", font, 16);
    nowPlaying.setPosition(40, 85);
    nowPlaying.setFillColor(sf::Color(130, 210, 255));

    sf::Text instructions(
        "Space: Play/Pause    Left: Previous    Right: Next",
        font, 13
    );
    instructions.setPosition(40, 510);
    instructions.setFillColor(sf::Color(180, 180, 180));

    sf::RectangleShape previousButton(sf::Vector2f(130, 45));
    previousButton.setPosition(145, 425);
    previousButton.setFillColor(sf::Color(55, 65, 90));

    sf::RectangleShape playButton(sf::Vector2f(130, 45));
    playButton.setPosition(315, 425);
    playButton.setFillColor(sf::Color(45, 115, 100));

    sf::RectangleShape nextButton(sf::Vector2f(130, 45));
    nextButton.setPosition(485, 425);
    nextButton.setFillColor(sf::Color(55, 65, 90));

    auto makeText = [&](const string& value, float x, float y)
    {
        sf::Text text(value, font, 16);
        text.setPosition(x, y);
        text.setFillColor(sf::Color::White);
        return text;
    };

    auto loadCurrentSong = [&]()
    {
        music.stop();
        isPlaying = false;

        Song* song = playlist.getCurrentSong();

        if (song == nullptr)
            return;

        if (!music.openFromFile(song->filePath))
        {
            cerr << "Unable to open audio: "
                 << song->filePath << endl;
            return;
        }

        music.play();
        isPlaying = true;
    };

    auto togglePlayback = [&]()
    {
        Song* song = playlist.getCurrentSong();

        if (song == nullptr)
            return;

        if (music.getStatus() == sf::SoundSource::Playing)
        {
            music.pause();
            isPlaying = false;
        }
        else if (music.getStatus() == sf::SoundSource::Paused)
        {
            music.play();
            isPlaying = true;
        }
        else
        {
            loadCurrentSong();
        }
    };

    auto nextTrack = [&]()
    {
        playlist.nextSong();
        loadCurrentSong();
    };

    auto previousTrack = [&]()
    {
        playlist.previousSong();
        loadCurrentSong();
    };

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                    togglePlayback();

                if (event.key.code == sf::Keyboard::Right)
                    nextTrack();

                if (event.key.code == sf::Keyboard::Left)
                    previousTrack();
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mouse(
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y)
                );

                if (previousButton.getGlobalBounds().contains(mouse))
                    previousTrack();
                else if (playButton.getGlobalBounds().contains(mouse))
                    togglePlayback();
                else if (nextButton.getGlobalBounds().contains(mouse))
                    nextTrack();
                else
                {
                    vector<Song> songs = playlist.getSongs();

                    for (int i = 0; i < static_cast<int>(songs.size()); i++)
                    {
                        sf::FloatRect row(40, 150 + i * 55, 680, 45);

                        if (row.contains(mouse))
                        {
                            playlist.selectSong(i);
                            loadCurrentSong();
                            break;
                        }
                    }
                }
            }
        }

        Song* current = playlist.getCurrentSong();

        if (current != nullptr)
            nowPlaying.setString(
                "Selected: " + current->title +
                " - " + current->artist
            );
        else
            nowPlaying.setString("No song selected");

        window.clear(sf::Color(22, 26, 37));

        window.draw(heading);
        window.draw(nowPlaying);
        window.draw(instructions);

        vector<Song> songs = playlist.getSongs();

        for (int i = 0; i < static_cast<int>(songs.size()); i++)
        {
            sf::RectangleShape row(sf::Vector2f(680, 45));
            row.setPosition(40, 150 + i * 55);
            row.setFillColor(sf::Color(40, 47, 63));

            window.draw(row);

            sf::Text songText = makeText(
                songs[i].title + " - " + songs[i].artist,
                55, 160 + i * 55
            );

            window.draw(songText);
        }

        window.draw(previousButton);
        window.draw(playButton);
        window.draw(nextButton);

        sf::Text previousText = makeText("Previous", 165, 436);
        sf::Text playText = makeText(
            isPlaying ? "Pause" : "Play", 355, 436
        );
        sf::Text nextText = makeText("Next", 525, 436);

        window.draw(previousText);
        window.draw(playText);
        window.draw(nextText);

        window.display();
    }

    music.stop();

    return 0;
}
