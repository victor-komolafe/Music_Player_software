

#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <limits>

class Song {
    friend std::ostream &operator<<(std::ostream &os, const Song &s);
    std::string name;
    std::string artist;
    int rating;
public:
    Song() = default;
    Song(std::string name="NULL", std::string artist="null", int rating=0)
            : name{name}, artist{artist}, rating{rating} {}
    std::string get_name() const {
        return name;
    }
    std::string get_artist() const {
        return artist;
    }
    int get_rating() const {
        return rating;
    }
    
    bool operator<(const Song &rhs) const  {
        return this->name < rhs.name;
    }
    
    bool operator==(const Song &rhs) const  {
        return this->name == rhs.name;
    }
};

std::ostream &operator<<(std::ostream &os, const Song &s) {
    os << std::setw(20) << std::left << s.name
       << std::setw(30) << std::left << s.artist
       << std::setw(2) << std::left << s.rating
       <<std::endl;
       return os;
}

void display_menu() {
    std::cout << "\nF - Play First Song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout <<"S - Find a song" <<std::endl;
    std::cout << "L - List the current playlist" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song &song) {

    std::cout << "Playing: \n"<<song.get_name()<<"\t"<<song.get_artist()<< std::endl;
}

void display_playlist(const std::list<Song> &playlist, const Song &current_song) {
    for(const auto &i: playlist){
        std::cout<<i;
    }
    play_current_song(current_song);

}

int main(){

    std::list<Song> playlist{
            {"God's Plan",        "Drake",                     5},
            {"Never Be The Same", "Camila Cabello",            5},
            {"Pray For Me",       "The Weekend and K. Lamar",  4},
            {"The Middle",        "Zedd, Maren Morris & Grey", 5},
            {"Wait",              "Maroone 5",                 4},
            {"Whatever It Takes", "Imagine Dragons",           3} ,
            // {"Pray For Me",       "Justin Beiber",  4}        not sure how to make multiple searches found 
    };
    
    std::list<Song>::iterator current_song = playlist.begin();
    auto one_end = playlist.end();  //stores iterator to last element in container
    std::advance(one_end,-1);
    char selection ;
    

    // std::cout << "Enter selcetin" << std::endl;
    // std::cin>>selection;
    // std::cout<<selection;
   
    do{
        display_menu();
        // std::cin.clear();
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cin>>selection;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        
  
        if(selection == 'f'|| selection ==  'F'){
            current_song = playlist.begin();
            play_current_song(*current_song);
        }
        
        if(selection =='p' || selection ==  'P'){
            if(current_song == playlist.begin())
                play_current_song(*current_song);
            else{
                std::advance(current_song,-1);
            }
            
        }
         if(selection =='s' || selection ==  'S'){
            std::cout<<"What is the name of the  song you are looking for? ";
            std::string song_name;
            std::getline(std::cin,song_name);
            // std::cout<<"who sang the song?";
            // std::string song_artist;
            // std::getline(std::cin,song_artist);
            auto find = std::find(playlist.begin(),playlist.end(),Song{song_name});
            

            if(find == playlist.end())
                std::cout<<"Sorry song not found in playlist";
            else{
                
               std::cout<<*find;
            }
            
        }
        if(selection == 'n' || selection == 'N'){
            
            // if(current_song!=playlist.end()){
            //     if(current_song!=one_end){
            //         std::advance(current_song,1);
            //         play_current_song(*current_song);
            //     } 
            //     else{
            //         if(current_song ==one_end ){
            //        current_song = playlist.begin(); 
            //        play_current_song(*current_song);
                   

            //     }}  
            // }
             std::advance(current_song,1);
             
             if(current_song==playlist.end()){
                   current_song = playlist.begin(); 
                 
            } 
            play_current_song(*current_song);
                
            //  else{
        }
        if(selection =='a' || selection ==  'A'){

            std::string name;
            std::string artist;
            int rating;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout<<"Enter the name of song: ";
            getline(std::cin,name);
            std::cout<<"Enter name of artist : ";
            getline(std::cin,artist);
            std::cout<<"Enter the rating: ";
            std::cin>>rating;
            
            playlist.emplace(current_song, Song{name,artist,rating});
            play_current_song(*current_song);
        }
        if(selection == 'l' || selection ==  'L'){

            for(const auto &j: playlist){
                std::cout<<j;
            }
         }
     
        else{std::cout<<"ILLEGAL CHOICE";}
    } while(selection != 'Q' && selection !='q');

       
        // std::cin.clear();
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    // Your program logic goes here

    std::cout << "Thanks for listening!" << std::endl;
    return 0;
}