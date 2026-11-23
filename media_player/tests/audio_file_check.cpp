#include <SFML/Audio.hpp>
#include <iostream>
int main(int argc,char** argv){
 if(argc<2){std::cerr<<"usage: audio_file_check <mp3>\n";return 2;}
 sf::Music music;
 if(!music.openFromFile(argv[1])){std::cerr<<"FAIL: audio load\n";return 1;}
 std::cout<<"PASS: MP3 loaded, duration="<<music.getDuration().asSeconds()<<"s\n";
 return 0;
}
