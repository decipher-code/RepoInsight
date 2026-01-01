graph [
  directed 1
  node [
    id 0
    label "loadUsersFromFile(set<User*>&#38; users)"
  ]
  node [
    id 1
    label "getline"
  ]
  node [
    id 2
    label "load_songs(vector<Song*>&#38; allsongs)"
  ]
  node [
    id 3
    label "main()"
  ]
  node [
    id 4
    label "loadUsersFromFile"
  ]
  node [
    id 5
    label "load_songs"
  ]
  node [
    id 6
    label "saveUsersToFile"
  ]
  node [
    id 7
    label "save_songs"
  ]
  node [
    id 8
    label "MusicPlayerApp::run()"
  ]
  node [
    id 9
    label "registerUser"
  ]
  node [
    id 10
    label "loginUser"
  ]
  node [
    id 11
    label "displayMainMenu"
  ]
  node [
    id 12
    label "MusicPlayerApp::registerUser()"
  ]
  node [
    id 13
    label "addDefaultSongsForNewUser"
  ]
  node [
    id 14
    label "MusicPlayerApp::loginUser()"
  ]
  node [
    id 15
    label "MusicPlayerApp::displayMainMenu()"
  ]
  node [
    id 16
    label "displaySongMenu"
  ]
  node [
    id 17
    label "displayPlaylistMenu"
  ]
  node [
    id 18
    label "MusicPlayerApp::displaySongMenu()"
  ]
  node [
    id 19
    label "createNewSong"
  ]
  node [
    id 20
    label "setw"
  ]
  node [
    id 21
    label "MusicPlayerApp::displayPlaylistMenu()"
  ]
  node [
    id 22
    label "selectPlaylist"
  ]
  node [
    id 23
    label "InsidePlaylistMenu"
  ]
  node [
    id 24
    label "MusicPlayerApp::InsidePlaylistMenu(Playlist* playlist)"
  ]
  node [
    id 25
    label "displayHeader() const"
  ]
  node [
    id 26
    label "AddSong(const Song&#38; newsong)"
  ]
  node [
    id 27
    label "DuplicateSongException"
  ]
  node [
    id 28
    label "removeSong(const Song&#38; song)"
  ]
  node [
    id 29
    label "SongNotFoundException"
  ]
  node [
    id 30
    label "showAllSongs() const"
  ]
  node [
    id 31
    label "PlaylistException"
  ]
  node [
    id 32
    label "displayHeader"
  ]
  node [
    id 33
    label "setprecision"
  ]
  node [
    id 34
    label "shufflePlaylist()"
  ]
  node [
    id 35
    label "shuffle"
  ]
  node [
    id 36
    label "loopPlaylist(int times = 1)"
  ]
  node [
    id 37
    label "PlayPlaylist"
  ]
  node [
    id 38
    label "searchByTitle(const string&#38; title) const"
  ]
  node [
    id 39
    label "searchByArtist(const string&#38; artist) const"
  ]
  node [
    id 40
    label "searchByGenre(const string&#38; genre) const"
  ]
  node [
    id 41
    label "PlayPlaylist()"
  ]
  node [
    id 42
    label "PrintAdRed"
  ]
  node [
    id 43
    label "getsongs"
  ]
  node [
    id 44
    label "PrintAdRed(const string&#38; ad)"
  ]
  node [
    id 45
    label "GetStdHandle"
  ]
  node [
    id 46
    label "GetConsoleScreenBufferInfo"
  ]
  node [
    id 47
    label "SetConsoleTextAttribute"
  ]
  node [
    id 48
    label "PlaySong() const"
  ]
  node [
    id 49
    label "loadPlaylists()"
  ]
  node [
    id 50
    label "Song"
  ]
  edge [
    source 0
    target 1
  ]
  edge [
    source 2
    target 1
  ]
  edge [
    source 3
    target 4
  ]
  edge [
    source 3
    target 5
  ]
  edge [
    source 3
    target 6
  ]
  edge [
    source 3
    target 7
  ]
  edge [
    source 8
    target 9
  ]
  edge [
    source 8
    target 10
  ]
  edge [
    source 8
    target 11
  ]
  edge [
    source 12
    target 1
  ]
  edge [
    source 12
    target 13
  ]
  edge [
    source 14
    target 1
  ]
  edge [
    source 15
    target 16
  ]
  edge [
    source 15
    target 17
  ]
  edge [
    source 18
    target 19
  ]
  edge [
    source 18
    target 20
  ]
  edge [
    source 21
    target 1
  ]
  edge [
    source 21
    target 22
  ]
  edge [
    source 21
    target 23
  ]
  edge [
    source 24
    target 1
  ]
  edge [
    source 25
    target 20
  ]
  edge [
    source 26
    target 27
  ]
  edge [
    source 28
    target 29
  ]
  edge [
    source 30
    target 31
  ]
  edge [
    source 30
    target 32
  ]
  edge [
    source 30
    target 20
  ]
  edge [
    source 30
    target 33
  ]
  edge [
    source 34
    target 31
  ]
  edge [
    source 34
    target 35
  ]
  edge [
    source 36
    target 31
  ]
  edge [
    source 36
    target 37
  ]
  edge [
    source 38
    target 32
  ]
  edge [
    source 38
    target 20
  ]
  edge [
    source 38
    target 33
  ]
  edge [
    source 38
    target 29
  ]
  edge [
    source 39
    target 32
  ]
  edge [
    source 39
    target 20
  ]
  edge [
    source 39
    target 33
  ]
  edge [
    source 39
    target 29
  ]
  edge [
    source 40
    target 32
  ]
  edge [
    source 40
    target 20
  ]
  edge [
    source 40
    target 33
  ]
  edge [
    source 40
    target 29
  ]
  edge [
    source 41
    target 42
  ]
  edge [
    source 41
    target 43
  ]
  edge [
    source 44
    target 45
  ]
  edge [
    source 44
    target 46
  ]
  edge [
    source 44
    target 47
  ]
  edge [
    source 48
    target 20
  ]
  edge [
    source 48
    target 33
  ]
  edge [
    source 49
    target 1
  ]
  edge [
    source 49
    target 50
  ]
]
