#include "SortedSongPlaylist.h"
#include "SortedArrayPlaylist.h"
#include "UnsortedArrayPlaylist.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using Clock=chrono::steady_clock;
static Song song(int i) { return Song("Track_"+to_string(100000+i),"Benchmark",120,"sample.mp3"); }
int main(){
 cout << "type,n,m,merge_microseconds\n";
 for(int n: {100,1000,10000}){
   int m=n;
   SortedArrayPlaylist a,b;
   SortedSongPlaylist l,r;
   for(int i=0;i<n;i++){a.addSong(song(i*2)); l.addSong(song(i*2));}
   for(int i=0;i<m;i++){b.addSong(song(i*2+1)); r.addSong(song(i*2+1));}
   auto start=Clock::now(); a.mergeSortedPlaylists(b); auto end=Clock::now();
   cout<<"sorted_array,"<<n<<","<<m<<","<<chrono::duration_cast<chrono::microseconds>(end-start).count()<<"\n";
   start=Clock::now(); l.mergeSortedPlaylists(r); end=Clock::now();
   cout<<"sorted_linked,"<<n<<","<<m<<","<<chrono::duration_cast<chrono::microseconds>(end-start).count()<<"\n";
 }
}
