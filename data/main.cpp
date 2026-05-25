#include<bits/stdc++.h>
#include "error_handling.h"
#include "song.h"
#include "playlist.h"
#include "user.h"
#include "musicplayerapp.h"

using namespace std;

// Function to save users to file
void saveUsersToFile(const set<User*>& users) {
    ofstream out("users_data.txt");
    if (!out) {
        cerr << "Error: Could not open users file for writing\n";
        return;
    }

    out << users.size() << "\n";
    for (const User* user : users) {
        out << user->getUsername() << "\n"
            << user->getEmail() << "\n"
            << user->IsPremiumUser() << "\n";
    }
    
    if (!out) {
        cerr << "Error: Failed to write all user data\n";
    } else {
        cout << "User data saved successfully\n";
    }
}

// Function to load users from file
void loadUsersFromFile(set<User*>& users) {
    ifstream in("users_data.txt");
    if (!in.is_open()) {
        cout << "No existing user data found (normal for first run)\n";
        return;
    }

    int userCount;
    in >> userCount;
    in.ignore(); // Skip newline after count

    for (int i = 0; i < userCount; ++i) {
        string username, email;
        bool isPremium;

        getline(in, username);
        getline(in, email);
        in >> isPremium;
        in.ignore(); // Skip newline after premium status

        User* newUser = new User(username, email);
        if (isPremium) {
            newUser->upgradeToPremium();
        }
        users.insert(newUser);
    }

    cout << "Loaded " << users.size() << " users\n";
}


void save_songs(const vector<Song*>& allsongs) {
    ofstream myfile("songs.txt"); 
    
    if (!myfile.is_open()) {
        cerr << "Error: Could not save songs to file!" << endl;
        return;
    }

    for (Song* song : allsongs) {
        myfile << song->getTitle() << "\n"
               << song->getArtist() << "\n"
               << song->getGenre() << "\n"
               << song->getDuration() << "\n";
    }
    cout << "Songs saved successfully!" << endl;
}

void load_songs(vector<Song*>& allsongs) {  
    ifstream myfile("songs.txt");
    
    if (!myfile.is_open()) {
        cerr << "No existing song data found." << endl;
        return;
    }

    string title, artist, genre;
    double duration;

    
    for (Song* song : allsongs) delete song;
    allsongs.clear();

    while (getline(myfile, title) && 
           getline(myfile, artist) && 
           getline(myfile, genre) && 
           (myfile >> duration)) {
        
        myfile.ignore();  
        allsongs.push_back(new Song(title, artist, genre, duration));
    }
    cout << "Loaded " << allsongs.size() << " songs." << endl;
}



int main() {

        MusicPlayerApp app;
        set<User*>& users = app.getUsers();
    
    
        loadUsersFromFile(users);
      
        load_songs(app.getAllSongs());
    
        app.run();
    
        cout << "\nSaving all data before exit...\n";
    
    
        saveUsersToFile(users);
        save_songs(app.getAllSongs());
    
        
        
        cout << "Songs saved successfully!" << endl;
        app.run();
        return 0;
}