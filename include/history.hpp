#include "simdjson.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

namespace sj = simdjson;

struct SongTime{
    char uri[36];
    unsigned int s;
};

struct ArtistTime{
    std::string artist;
    unsigned int s;
};

class History{
    public:
        void Loader(std::string path);
        void Print();
        void Print(int min);
        void Print(int min_art, int min_song);
        void SortSongs(std::vector<SongTime>& songs);
        template <typename T, typename Proj>
        void SortSongs(std::vector<T>& items, Proj getter);
        void Sort();
        void PrintTop();
        void PrintTop(int n);
        void MoveToVector();
    private:
        sj::ondemand::parser parser;
        // track uri to ms
        std::unordered_map<std::string, long long> music_map;
        // artist name to ms
        std::unordered_map<std::string, long long> artist_map;

        std::unordered_map<std::string, std::string> name_map;
        std::unordered_set<std::string> timestamps;

        std::vector<ArtistTime> artists;
        std::vector<SongTime> songs;

        long long total = 0;
};