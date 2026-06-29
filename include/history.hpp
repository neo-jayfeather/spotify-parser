#include "simdjson.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <filesystem>

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
        void Load(std::string path);
        void LoadFound();
        void LoadFound(int year);
        void LoadFound(std::vector<int> year);
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
        void FindFiles(const std::string& path);
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

        std::vector<std::filesystem::path> json_files;

        long long total = 0;
};