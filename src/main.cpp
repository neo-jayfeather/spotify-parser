#include <iostream>
#include "history.hpp"

int main() {
    History parser;
    parser.Loader("Streaming_History_Audio_2025.json");
    parser.Loader("Streaming_History_Audio_2025_1.json");
    parser.Loader("Streaming_History_Audio_2025_2.json");
    parser.Print();
    return 0;
}