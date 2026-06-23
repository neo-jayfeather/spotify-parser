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
        element["ts"].get(temp_ts); // repetition sometimes
        if(timestamps.count(temp_ts) == 1) continue;
        timestamps.insert(temp_ts);

        element["spotify_track_uri"].get(temp_uri); // use uri- constant length, prevent collisions
        element["master_metadata_album_artist_name"].get(temp_artist);
        // count unordered map
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


void History::Print(){
    for (auto element : music_map){
        
        std::cout << name_map[element.first] << " played for " << element.second / 1000 << "\n";
    }

    for(auto element : artist_map){
        std::cout << element.first << " played for " << element.second / 1000 << "\n";
    }

    std::cout << total << std::endl;
};