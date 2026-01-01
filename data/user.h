#include<bits/stdc++.h>
#include "error_handling.h"
#include "song.h"
#include "playlist.h"

using namespace std;



class User{
    private:
        string username;
        string email;
        vector<Playlist*>playlists;
        bool isPremiumUser = false;

    public:
        User(string name, string e){
            username = name;
            email = e;
        }

        string getUsername() const { return username; }
        string getEmail() const { return email; }
        int getPlaylistCount() const { return playlists.size() ;}
        vector<Playlist*> getPlaylists() const { return playlists; }
        bool IsPremiumUser() const { return isPremiumUser; }
        void setPremiumStatus(bool status) {
            isPremiumUser = status;
        }

        //other stuffs

        void displayProfile() const {
            cout << "\n User Profile:\n";
            if(isPremiumUser){
                cout<<"Premium User"<<endl;
            }
            else{
                cout<<"Regular User"<<endl;
            }
            cout << "Username: " << username << "\n";
            cout << "Email: " << email << "\n";
            cout << "Playlists: " << playlists.size() << "\n";
            
            
        }


        void upgradeToPremium() {
            isPremiumUser = true;
            cout << username << " upgraded to premium!\n";
        }



        //playlists of the user management

        void CreatePlaylist(string name){
            for(auto p : playlists){
                if(p->getName() == name){
                    cout << " Playlist '" << name << "' is already exist!\n";
                    return ;
                }
            }
            Playlist* newPlaylist = nullptr;
            if (isPremiumUser) {
                newPlaylist = new PremiumPlaylist(name);  // Premium playlist //polymorphism
            } else {
                newPlaylist = new Playlist(name);  // Regular playlist
            }
            playlists.push_back(newPlaylist);
            cout << " Playlist '" << name << "' created\n";
        }


        void DeletePlaylist(string name){
            auto it = playlists.begin();
            bool found = false;

            for(it = playlists.begin(); it != playlists.end(); ++it){
                if((*it)->getName() == name){       // playlists vector has pointer of Playlist so,, 
                    found = true;
                    break;
                }
            }
            if(found){
                Playlist* toDelete = *it;
                delete toDelete;
                playlists.erase(it);
                cout << "Deleted playlist: " << name << endl;
            } else {
                cout << "Playlist not found." << endl;
            }
        }


        void DisplayAllPlaylist(){
            if(playlists.empty()){
                cout<<"You have not created any playlist yet"<<endl;
                return;
            }

            cout << "\n Your Playlists: \n";
            cout << "-------------------------------------------\n";
            int index = 1;
            for(auto& p:playlists){
                cout<<index++ <<". "<<p->getName()<<" : "<<p->get_No_of_songs()<<" songs"<<endl;
            }
            cout << "-------------------------------------------\n";
        }


        void savePlaylists() const {
            string filename = username + "_playlists.txt";
            ofstream out(filename);
            
            if (!out) {
                cerr << "Error: Could not open file " << filename << " for writing\n";
                return;
            }
            
            out << playlists.size() << "\n";
            for (auto p : playlists) {
                out << p->getName() << "\n";
                const vector<Song>& songs = p->getsongs();
                out << songs.size() << "\n";
                for (const Song& s : songs) {
                    out << s.getTitle() << "\n"
                        << s.getArtist() << "\n"
                        << s.getGenre() << "\n"
                        << s.getDuration() << "\n";
                }
            }
            
            if (!out) {
                cerr << "Error: Failed to write all data to " << filename << "\n";
            }
            else {
                cout << "Playlists saved successfully to " << filename << "\n";
            }
        }
        
        void loadPlaylists() {
            string filename = username + "_playlists.txt";
            ifstream in(filename);
            
            if (!in.is_open()) {
                cout << "No existing playlists found for user " << username << "\n";
                return;
            }
            
            // Clear existing playlists to avoid duplicates
            for (auto p : playlists) {
                delete p;
            }
            playlists.clear();
            
            int playlistCount;
            in >> playlistCount;
            in.ignore();  // Skip the newline after playlistCount
            
            for (int i = 0; i < playlistCount; ++i) {
                string playlistName;
                getline(in, playlistName);
                
                Playlist* p = isPremiumUser ? new PremiumPlaylist(playlistName) : new Playlist(playlistName);
                int songCount;
                in >> songCount;
                in.ignore();  // Skip the newline after songCount
                
                for (int j = 0; j < songCount; ++j) {
                    string title, artist, genre;
                    double duration;
                    
                    getline(in, title);
                    getline(in, artist);
                    getline(in, genre);
                    in >> duration;
                    in.ignore();  // Skip the newline after duration
                    
                    p->AddSong(Song(title, artist, genre, duration));
                }
                playlists.push_back(p);
            }
            
            cout << "Loaded " << playlists.size() << " playlists from " << filename << "\n";
        }
        

        
};