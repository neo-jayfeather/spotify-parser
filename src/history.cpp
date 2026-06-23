#include "history.hpp"

void History::Loader(std::string path){
    auto json = sj::padded_string::load(path);
    sj::ondemand::document music = parser.iterate(json);


    std::string temp_uri;
    std::string temp_ts;
    std::string temp_name;
    std::string temp_artist;
    uint64_t temp_int;
    
    temp_uri.reserve(36);
    temp_ts.reserve(20);

    temp_name.reserve(30);
    temp_artist.reserve(30);

    for (auto element : music) { 
        element["ts"].get(temp_ts); // repetition sometimes, check with timestamp
        if(timestamps.count(temp_ts) == 1) continue; // skip
        timestamps.insert(temp_ts);

        element["spotify_track_uri"].get(temp_uri); // use uri- constant length, prevent collisions
        element["master_metadata_album_artist_name"].get(temp_artist);
        if(name_map.count(temp_uri) == 0){
            element["master_metadata_track_name"].get(temp_name);

            name_map[temp_uri] = temp_artist + " - " + temp_name;
        }

        temp_int = element["ms_played"].get_uint64();

        if(temp_int > 5000){
            music_map[temp_uri] += temp_int;
            artist_map[temp_artist] += temp_int;
            total += temp_int;
        }
    }
    return;
};

void History::MoveToVector(){
    SongTime temp_song;
    for(auto element : music_map){
        temp_song.s = static_cast<unsigned int>(element.second / 1000);
        std::memcpy(temp_song.uri, element.first.data(), 36);
        songs.emplace_back(temp_song);
    }

    for(auto element : artist_map){
        artists.emplace_back((struct ArtistTime){element.first, static_cast<unsigned int>(element.second / 1000)});
    }
}

void History::Print(int min_art, int min_song){
    for (auto element : music_map){
        if(element.second / 1000 > min_song)
            std::cout << name_map[element.first] << " played for " << element.second / 1000 << "\n";
    }

    for(auto element : artist_map){
        if(element.second / 1000 > min_art)
            std::cout << element.first << " played for " << element.second / 1000 << "\n";
    }

    std::cout << total << std::endl;
};

void History::Print(int min){
    Print(min, min);
};

void History::Print(){
    Print(0, 0);
}


// void History::SortSongs(std::vector<SongTime>& songs) {
//     std::sort(songs.begin(), songs.end(), [](const SongTime& a, const SongTime& b) {
//         return a.s < b.s;
//     });
// }

template <typename T, typename Proj>
void History::SortSongs(std::vector<T>& items, Proj getter) {
    std::sort(items.begin(), items.end(), [&](const T& a, const T& b) {
        return getter(a) < getter(b);
    });
}

void History::Sort(){
    SortSongs(songs, [](const SongTime& st){return st.s;});
    SortSongs(artists, [](const ArtistTime& at){return at.s;});
}

void History::PrintTop(int n){
    if(n > songs.size()) n = songs.size();
    std::string temp_str;
    for(int i = songs.size() - 1; i > songs.size() - n - 1; i--){
        temp_str = std::string(songs[i].uri, songs[i].uri + sizeof(songs[i].uri));
        std::cout << name_map[temp_str] << " played for " << (double) (songs[i].s / 360) / 10 << "h\n";
    }

    if(n > artists.size()) n = artists.size();

    for(int i = artists.size() - 1; i > artists.size() - n - 1; i--){
        std::cout << artists[i].artist << " played for " << (double) (artists[i].s / 360) / 10 << "h\n";
    }

    std::cout << (double) (total / 1000 / 360) / 10 << "h total.\n";
}

void History::PrintTop(){
    PrintTop(10);
}