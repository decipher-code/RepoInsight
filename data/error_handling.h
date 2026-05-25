#include<bits/stdc++.h>
#include<windows.h>

using namespace std;




// Custom exception classes
class SongNotFoundException : public exception {
    public:
        const char* what() const noexcept override {
            return "Song not found in playlist.";
        }
};

class DuplicateSongException : public exception {
    public:
        const char* what() const noexcept override {
            return "Song already exists in the playlist.";
        }
};

class PlaylistException : public exception {
    public:
        const char* what() const noexcept override {
            return "Playlist is empty.";
        }
};