#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include "SDL.h"
#include <limits>

using std::vector;

enum class State { kEmpty, kClosed, kOpen, kPath, };

class Node {
public:
    Node *parent = nullptr;
    int x = 0;
    int y = 0;
    int g_cost = 0;
    int h_cost = std::numeric_limits<int>::max();
    State state = State::kEmpty;
};

class Search {
public:
    Search(const std::size_t grid_width, const std::size_t grid_height);
    ~Search() {} 

    vector<SDL_Point> SearchWithPoints(const SDL_Point &start_point, const SDL_Point &end_point);


private:
    vector<vector<Node>> nodes;
    vector<Node> open_list{};
    constexpr static int delta [4][2]{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
    
    int CalculateHeuristic(int startX, int startY, int endX, int endY);
    bool CheckValidCell(const int x, const int y);
    std::pair<std::vector<SDL_Point>, std::vector<Node>> ProcessNeighbors(const std::vector<std::vector<Node>>& nodes,
                                                                       const std::vector<int>& delta,
                                                                       const SDL_Point& end_point,
                                                                       std::vector<Node>& open_list,
                                                                       Node* current,
                                                                       std::vector<SDL_Point>& results); 

};

#endif