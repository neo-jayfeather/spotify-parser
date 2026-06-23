#include "simdjson.h"
#include <unordered_map>
#include <unordered_set>

namespace sj = simdjson;

class History{
    public:
        void Loader(std::string path);
        void Print();
    private:
        sj::ondemand::parser parser;
        std::unordered_map<std::string, unsigned long> music_map;
        std::unordered_map<std::string, unsigned long> artist_map;
        std::unordered_map<std::string, std::string> name_map;
        std::unordered_set<std::string> timestamps;
        unsigned long long total = 0;
};