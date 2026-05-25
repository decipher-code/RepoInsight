#include<bits/stdc++.h>
#include<windows.h>

using namespace std;



void PrintAdRed(const string& ad) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << ad << endl;

    SetConsoleTextAttribute(hConsole, saved_attributes);
}





class Song{
	private:
		string Title;
		string Artist;
		string Genre;
		double Duration;
		
	public:
	
	    Song() : Title(""), Artist(""), Genre(""), Duration(0.0) {}
	    
	    Song(string t, string A, string G, double duration){
	        Title =t;
	        Artist = A;
	        Genre = G;
	        Duration = duration;
	      
	    }
	    
	    string getTitle() const{ return Title; }
	    string getArtist() const{ return Artist; }
	    string getGenre() const{ return Genre; }
	    double getDuration() const {return Duration; }
	   
	    
	    void PlaySong() const {
	        cout<<endl;
        	cout << "----------------------------------------" << endl;
            cout << "             Now Playing                " <<endl;
            cout << "----------------------------------------" << endl;
        
            cout << "| Title:   " << setw(27) << left << Title << " |" << endl;   // set(27)???
            cout << "| Artist:  " << setw(27) << left << Artist << " |" << endl;
            cout << "| Genre:   " << setw(27) << left << Genre << " |" << endl;
            
            
            stringstream durStream;  // ???
            durStream << fixed << setprecision(2) << Duration << " mins";    // ???
            
            string dur = durStream.str();
            
            cout << "| Duration: " << setw(27) << left << dur << "|" << endl;
        
                
            cout << "------------------------------------" << endl;
        }
        
        friend istream& operator>>(istream& is, Song& s) { // istream & ostream???
            cout << "Enter Song Title: ";
             
            getline(is, s.Title); // ???
        
            cout << "Enter Artist Name: ";
            getline(is, s.Artist);
        
            cout << "Enter Genre: ";
            getline(is, s.Genre);
        
            cout << "Enter Duration (in mins): ";
            is >> s.Duration;
        
            return is;
        }


        friend ostream& operator<<(ostream& os, const Song& s) {
            os << s.Title << "\n"
               << s.Artist << "\n"
               << s.Genre << "\n"
               << s.Duration << "\n";
            return os;
        }

		
};