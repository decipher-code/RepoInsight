#include<bits/stdc++.h>
#include "error_handling.h"
#include "song.h"
#include "playlist.h"
#include "user.h"

using namespace std;



class MusicPlayerApp {
    private:
        vector<Song*> allSongs;  
        set<User*> users;     
        User* currentUser;       
    
        // Helper functions
        void displayMainMenu();
        void displaySongMenu();
        void displayPlaylistMenu();
        void InsidePlaylistMenu(Playlist* playlist);
        Song* createNewSong();
        Playlist* selectPlaylist();

        
        public:

        MusicPlayerApp() : currentUser(nullptr) {}
        ~MusicPlayerApp(){
            for (auto song : allSongs) delete song;
            for (auto user : users) delete user;
        }
        set<User*>& getUsers() { return users; }
        User* getCurrentUser() const { return currentUser; }
        vector<Song*>& getAllSongs() { return allSongs; }


        void run();
        void registerUser();
        void loginUser();
        
        
        
        void addDefaultSongsForNewUser() {
            vector<tuple<string, string, string, double>> defaults = {
                {"Perfect", "Ed Sheeran", "Pop", 4.5},
                {"Believer", "Imagine Dragons", "Rock", 3.9},
                {"Stay", "Justin Bieber", "Pop", 2.8},
                {"Shape of You", "Ed Sheeran", "Pop", 4.2},
                {"Counting Stars", "OneRepublic", "Pop", 4.0}
            };
        
            for (auto& t : defaults) {
                string title = get<0>(t);
                string artist = get<1>(t);
                string genre = get<2>(t);
                double duration = get<3>(t);
            
                allSongs.push_back(new Song(title, artist, genre, duration));
            }
            
        }
        
    };
    
    
    // Main application loop
    void MusicPlayerApp::run() {
        
        while (true) {
            if (!currentUser) {
                cout << "\n===== Welcome to the Music Playlist Manager =====\n";
                cout << "1. Register\n";
                cout << "2. Login\n";
                cout << "3. Exit\n";
                cout << "Choice: ";
                
                int choice;
                cin >> choice;
                cin.ignore();  
                
                switch (choice) {
                    case 1: registerUser(); break;
                    case 2: loginUser(); break;
                    case 3: return;
                    default: cout << "Invalid choice!\n";
                }
            } else {
                displayMainMenu();
            }
        }
    }
    
    // User registration
    void MusicPlayerApp::registerUser() {
        string username, email;
        cout << "Enter username: ";
        getline(cin, username);
    
        for (User* u : users) {
            if (u->getUsername() == username) {
                cout << "Username '" << username << "' already exists!\n";
                return;
            }
        }
    
        cout << "Enter email: ";
        getline(cin, email);
    
        User* newuser = new User(username, email);
    
        cout << "Choose Account type: 1. Regular  2. Premium: ";
        int choice; 
        cin >> choice;
        if (choice == 2) {
            newuser->upgradeToPremium();
        }
    
        addDefaultSongsForNewUser();  
    
        users.insert(newuser);
        currentUser = newuser;
        cout << "Registration successful!\n";
    }
    
    
    
    void MusicPlayerApp::loginUser() {
        if (users.empty()) {
            cout << "No users found! Please register first.\n";
            return;
        }
    
        cout << "\n=== Registered Users ===\n";
        for (User* u : users) {
            cout << "- " << u->getUsername() << "\n";
        }
    
        string username;
        cout << "\nEnter username: ";
        getline(cin, username);
    
        for (User* u : users) {
            if (u->getUsername() == username) {
                currentUser = u;
                cout << "Welcome back, " << username << "!\n";
                currentUser->loadPlaylists(); // Load user's playlist data
                return;
            }
        }
    
        cout << "User not found!\n";
    }
    
    
    // Main menu for logged-in users
    void MusicPlayerApp::displayMainMenu() {
        cout << "\n===== Main Menu =====\n";
        cout << "Welcome, " << currentUser->getUsername() << "!\n";
        cout << "1. Songs Library\n";
        cout << "2. My Playlists\n";
        cout << "3. My Profile\n";
        cout << "4. Logout\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore();  
    
        switch (choice) {
            case 1: displaySongMenu(); break;
            case 2: displayPlaylistMenu(); break;
            case 3: {
                currentUser->displayProfile(); 
                cout<<"Do want to change the Account type: 1.Regular  2.Premium"<<endl;
                int choice;
                cin>>choice;
                if(choice == 2){
                    currentUser->upgradeToPremium();
                }
                else{
                    currentUser->setPremiumStatus(false);
                }
                break;
            } 
            case 4: {
                if (currentUser) {
                    currentUser->savePlaylists();
                    currentUser = nullptr;
                }
                currentUser = nullptr;
                return;  // Return to login screen
            }
            default: cout << "Invalid choice! Please try again.\n";
        }
    }
    
    // Song management menu
    void MusicPlayerApp::displaySongMenu() {
        while (true) {
            cout << "\n===== Songs Library =====\n";
            cout << "1. Add New Song to Library\n";
            cout << "2. View All Songs\n";
            cout << "3. Play a Song\n";
            cout << "4. Back to Main Menu\n";
            cout << "Choice: ";
            
            int choice;
            cin >> choice;
            cin.ignore();
            
            switch (choice) {
                case 1: {
                    Song* newSong = createNewSong();
                    allSongs.push_back(newSong);
                    cout << "Song added to library!\n";
                    break;
                }
                case 2: {
                    if (allSongs.empty()) {
                        cout << "No songs in library!\n";
                        break;
                    }
                    cout << "\n===== All Songs =====\n";
    
                    cout << left << setw(5) << "#"
                     << setw(25) << "Title"
                     << setw(20) << "Artist\n";
                    
                     int index=1;
                    for (size_t i = 0; i < allSongs.size(); i++) {
                        cout << left << setw(5) << index++
                         << setw(25) << allSongs[i]->getTitle()
                         << setw(20) << allSongs[i]->getArtist()<< "\n";
                    }
                    break;
                }
                case 3: {
                    
                    cout << "\nAvailable Songs:\n";
                    for (size_t i = 0; i < allSongs.size(); i++) {
                        cout << i+1 << ". " << allSongs[i]->getTitle() << "\n";
                    }
    
                    cout << "Enter song number to play: ";
                    int choice;
                    cin >> choice;
                    cin.ignore();
    
                    
                    if (choice >= 1 && choice <= allSongs.size()) {
                        allSongs[choice-1]->PlaySong(); 
                    } else {
                        cout << "Invalid selection!\n";
                    }
                    break;
                }
                case 4: return;
                default: cout << "Invalid choice!\n";
            }
        }
    }
    
    
    void MusicPlayerApp::displayPlaylistMenu(){
        while(true){
            cout << "\n===== Playlist Menu =====\n";
            cout << "1. Create Playlist\n";
            cout << "2. Show All Playlist\n";
            cout << "3. Select Playlist\n";
            cout << "4. Delete Playlist\n";
            cout << "5. Back to Playlist Selection\n";
            cout << "Choice: ";
            int choice;
            cin >> choice;
            cin.ignore();
            
            try {
                switch (choice) {
                    case 1:{
                        cout<<"Enter the name of the Playlist: ";
                        string n;
                        getline(cin, n);
                        currentUser->CreatePlaylist(n);
                        break;
                    } 
                    case 2: currentUser->DisplayAllPlaylist(); break;
                    case 3: {
                        Playlist* currPlaylist = selectPlaylist();
                        InsidePlaylistMenu(currPlaylist);
                        break;
                    }
                    case 4:{
                        string name;
                        cout << "Enter playlist name to delete: ";
                        getline(cin, name);
                        currentUser->DeletePlaylist(name); 
                        break;
                    } 
                    case 5: return;
                    default: cout << "Invalid choice!\n";
                }
            } catch (const exception& e) {
                cout << "Error: " << e.what() << "\n";
            }
        }
    }
    
    // Playlist-specific menu
    void MusicPlayerApp::InsidePlaylistMenu(Playlist* playlist) {
        while (true) {
            cout << "\n===== Current Playlist: " << playlist->getName() << " =====\n";
            cout << "1. Play Playlist\n";
            cout << "2. View Songs\n";
            cout << "3. Add Song\n";
            cout << "4. Remove Song\n";
            cout << "5. Shuffle Playlist\n";
            cout << "6. Loop Playlist\n";
            cout << "7. Search in Playlist\n";
            cout << "8. Back to Playlist Selection\n";
            cout << "Choice: ";
            
            int choice;
            cin >> choice;
            cin.ignore();
            
            try {
                switch (choice) {
                    case 1:{
                        playlist->PlayPlaylist(); break;
                    } 
                    case 2: playlist->showAllSongs(); break;
                    case 3: {
                        if (allSongs.empty()) {
                            cout << "No songs in library to add!\n";
                            break;
                        }
                        cout << "Select song to add:\n";
                        for (size_t i = 0; i < allSongs.size(); i++) {
                            cout << i+1 << ". " << allSongs[i]->getTitle() 
                                 << " by " << allSongs[i]->getArtist() << "\n";
                        }
                        cout << "Choice: ";
                        int songChoice;
                        cin >> songChoice;
                        cin.ignore();
                        
                        if (songChoice > 0 && songChoice <= allSongs.size()) {
                            playlist->AddSong(*allSongs[songChoice-1]);
                        } else {
                            cout << "Invalid choice!\n";
                        }
                        break;
                    }
                    case 4: {
                        cout << "Enter song title to remove: ";
                        string title;
                        getline(cin, title);
                        
                        // Create a temporary song object for searching
                        Song temp(title, "", "", 0.0);
                        playlist->removeSong(temp);
                        break;
                    }
                    case 5: playlist->shufflePlaylist(); break;
                    case 6: {
                        cout << "How many times to loop? ";
                        int times;
                        cin >> times;
                        cin.ignore();
                        playlist->loopPlaylist(times);
                        break;
                    }
                    case 7: {
                        cout << "Search by:\n1. Title\n2. Artist\n3. Genre\nChoice: ";
                        int searchType;
                        cin >> searchType;
                        cin.ignore();
                        
                        cout << "Enter search term: ";
                        string term;
                        getline(cin, term);
                        
                        switch (searchType) {
                            case 1: playlist->searchByTitle(term); break;
                            case 2: playlist->searchByArtist(term); break;
                            case 3: playlist->searchByGenre(term); break;
                            default: cout << "Invalid choice!\n";
                        }
                        break;
                    }
                    case 8: return;
                    default: cout << "Invalid choice!\n";
                }
            } catch (const exception& e) {
                cout << "Error: " << e.what() << "\n";
            }
        }
    }
    
    // Helper to create a new song
    Song* MusicPlayerApp::createNewSong() {
        Song* newSong = new Song();  // Create empty song object
        
        cin >> *newSong;  // Use the overloaded >> operator
        
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        return newSong;
    }
    
    // Helper to select a playlist
    Playlist* MusicPlayerApp::selectPlaylist() {
        
        if (currentUser->getPlaylistCount() == 0) {
            cout << "No playlists available. Create one first.\n";
            return nullptr;
        }
        currentUser->DisplayAllPlaylist();
    
    
        cout << "Enter playlist number: ";
        int choice;
        cin >> choice;
        cin.ignore();
        
        if (choice > 0 && choice <= currentUser->getPlaylistCount()) {
            return currentUser->getPlaylists()[choice-1];
        } else {
            cout << "Invalid choice!\n";
            return nullptr;
        }
    }