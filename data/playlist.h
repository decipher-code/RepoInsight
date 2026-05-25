#include<bits/stdc++.h>
#include "error_handling.h"
#include "song.h"

using namespace std;


class Playlist{
    private:
        string name;
        vector<Song> songs;
        
    public:
        Playlist(string title = "Untitled"){
            name = title;
        }

        // getName function
        string getName() const{ return name; } 
        int get_No_of_songs() const{ return songs.size(); }
        vector<Song> getsongs() const{ return songs; }


        void displayHeader() const {
            cout << left << setw(5) << "#"
                 << setw(25) << "Title"
                 << setw(20) << "Artist"
                 << setw(10) << "Genre"
                 << setw(10) << "Duration"<<endl;
            cout << "-----------------------------------------------------------------------------------\n";
        }




        // addsong function
        void AddSong(const Song& newsong){
            for(auto& s: songs){
                if(s.getTitle() == newsong.getTitle() && s.getArtist() == newsong.getArtist()){
                    throw DuplicateSongException();
                }
            }
            songs.push_back(newsong);
            cout << "Song added to playlist: " << name << endl;
        }
        



        // removesong function
        void removeSong(const Song& song) {
            
            bool found = false;
            for (auto it = songs.begin(); it != songs.end(); ++it) {
                if (it->getTitle() == song.getTitle() && it->getArtist() == song.getArtist()) {
                    songs.erase(it);
                    cout << "Removed song: " << song.getTitle() << " from playlist: " << name << endl;
                    found = true;
                    break;
                }
            }
            if(!found){
                throw SongNotFoundException(); 
            }
        }
        




        // showsongs function
        
        void showAllSongs() const {
            if (songs.empty()) {
                throw PlaylistException();
            }
        
            displayHeader();
        
            int index = 1;
            for (const Song& s : songs) {
                cout << left << setw(5) << index++
                     << setw(25) << s.getTitle()
                     << setw(20) << s.getArtist()
                     << setw(10) << s.getGenre()
                     << setw(10) << fixed << setprecision(2) << s.getDuration()
                     << "\n";
            }
            cout<<"\n";
        }
        




        void shufflePlaylist(){
            if(songs.empty()){
                throw PlaylistException();
            }
            random_device rd;
            mt19937 g(rd());
            shuffle(songs.begin(),songs.end(),g);
            cout<<"The Playlist has been shuffled."<<endl;
        }




        void loopPlaylist(int times = 1){
            if(songs.empty()){
                throw PlaylistException();
            }
            cout << "\nLooping playlist \"" << name << "\" " << times << " time(s):\n";
            for(int i=0;i<times;++i){
                cout << "\n--- Loop " << (i + 1) << " ---\n";
                PlayPlaylist();
            }
        }



        void searchByTitle(const string& title) const {
            bool found = false;
            cout << "\nSongs with title: " << title << "\n";


            displayHeader();


            int index = 1;
            for (const auto& song : songs) {
                if (song.getTitle() == title) {
                    cout << left << setw(5) << index++
                        << setw(25) << song.getTitle()
                        << setw(20) << song.getArtist()
                        << setw(10) << song.getGenre()
                        << setw(10) << fixed << setprecision(2) << song.getDuration()
                        << "\n";
                    found = true;
                }
            }
            if (!found) {
                throw SongNotFoundException(); 
            }
            cout << "\n";
        }

        void searchByArtist(const string& artist) const {
            bool found = false;

            displayHeader();

            int index = 1;
            for (const auto& song : songs) {
                if (song.getArtist() == artist) {
                    cout << left << setw(5) << index++
                        << setw(25) << song.getTitle()
                        << setw(20) << song.getArtist()
                        << setw(10) << song.getGenre()
                        << setw(10) << fixed << setprecision(2) << song.getDuration()
                        << "\n";
                    found = true;
                }
            }
            if (!found) {
                throw SongNotFoundException(); 
            }
            cout << "\n";
        }

        void searchByGenre(const string& genre) const {
            bool found = false;
            
            displayHeader();

            int index = 1;
            for (const auto& song : songs) {
                if (song.getGenre() == genre) {
                    cout << left << setw(5) << index++
                        << setw(25) << song.getTitle()
                        << setw(20) << song.getArtist()
                        << setw(10) << song.getGenre()
                        << setw(10) << fixed << setprecision(2) << song.getDuration()
                        << "\n";
                    found = true;
                }
            }
            if (!found) {
                throw SongNotFoundException(); 
            }
            cout << "\n";
        }



        virtual void PlayPlaylist() {
            if (songs.empty()) {
                cout << "Playlist is empty.\n";
                return;
            }
        
            vector<string> ads = {
                "Ad: Upgrade to Premium for an ad-free vibe!",
                "Ad: Brought to you by your midnight cravings.",
                "Ad: Music + Chill = Life."
            };
        
            size_t index = 0;
            string command;
            int playCount = 0;
            int adIndex = 0;
        
            while (true) {
                songs[index].PlaySong();
                playCount++;
        
                // After every 2 plays, show an ad
                if (playCount % 2 == 0) {
                    cout << "\n--- Ad Break ---\n";
                    cout<<"\n";
                    PrintAdRed(ads[adIndex]);
                    cout<<"\n";
                    cout << "----------------\n\n";
                    adIndex = (adIndex + 1) % ads.size(); // loop through ads
                }
        
                cout << "Enter command (next=d / prev=a / exit): ";
                cin >> command;
        
                if (command == "d") {
                    if (index < songs.size() - 1) {
                        index++;
                    } else {
                        cout<<"\n";
                        cout << "Already at last song.\n";
                    }
                }
                else if (command == "a") {
                    if (index > 0) {
                        index--;
                    } else {
                        cout<<"\n";
                        cout << "Already at first song.\n";
                    }
                }
                else if (command == "exit") {
                    break;
                }
                else {
                    cout<<"\n";
                    cout << "Invalid command.\n";
                }
            }
        }

      
};

































class PremiumPlaylist : public Playlist {
    public:
    
    PremiumPlaylist(string& name) : Playlist(name) {}

     void PlayPlaylist()
    {
        if(getsongs().empty()){
            cout << "Playlist is empty.\n";
            return;
        }
        size_t index = 0;
        string command;
    
        while(true){
            getsongs()[index].PlaySong();
            cout << "Enter command (next=d / prev=a/ exit): ";
            cin>>command;
        
            if(command=="d"){
                if(index<getsongs().size()-1){
                    index++;                
                }
                else
                cout<<"\n";
                cout << "Already at last song.\n";
            }
            else if(command=="a"){
                if(index>0){
                    index--;
                }
                else {
                    cout<<"\n";cout<<"Already at first song.\n";}
            }
            else if(command=="exit"){
                break;
            }
            else{cout<<"\n";
                cout<<"Invalid command"<<endl;
            }
        }
    }
};