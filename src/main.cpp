#include <iostream>
#include "history.hpp"

int main() {
    History parser;
    parser.FindFiles(".");
    parser.LoadFound(2026);
    // parser.Load("Streaming_History_Audio_2026.json");
    // parser.Load("Streaming_History_Audio_2025_1.json");
    // parser.Load("Streaming_History_Audio_2025_2.json");
    parser.MoveToVector();
    parser.Sort();
    parser.PrintTop();
    // parser.Print(600, 180);
    return 0;
}