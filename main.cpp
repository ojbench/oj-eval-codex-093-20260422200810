#include <bits/stdc++.h>
using namespace std;

// Directions: 0=up,1=right,2=down,3=left
static const int dr[4] = {-1, 0, 1, 0};
static const int dc[4] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> g(10, vector<int>(10));
    int sr = -1, sc = -1;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (!(cin >> g[i][j])) return 0; // invalid input
            if (g[i][j] == 4) { sr = i; sc = j; }
        }
    }

    if (sr == -1 || sc == -1) return 0; // safety

    // Surrounding walls outside the 10x10 are implicit; we just treat bounds as walls.

    // Pacman starts at (sr, sc) and initial direction is up (0)
    int r = sr, c = sc;
    int dir = 0;
    long long score = 0;

    // Right-hand rule priority: right, straight, left, back
    auto next_dir_priority = [&](int cur) {
        array<int,4> order{ (cur+1)&3, cur, (cur+3)&3, (cur+2)&3 };
        return order;
    };

    // Loop detection: movement depends only on walls and current direction (beans don't affect passability).
    // If a (r,c,dir) state repeats, Pacman will loop forever without hitting a ghost.
    struct State { int r,c,d; };
    struct StateHash { size_t operator()(const State& s) const noexcept {
        return (s.r*10 + s.c) * 131u + s.d;
    }};
    struct StateEq { bool operator()(const State& a, const State& b) const noexcept {
        return a.r==b.r && a.c==b.c && a.d==b.d;
    }};
    unordered_set<State, StateHash, StateEq> seen;
    seen.reserve(1<<12);

    // If starting on a bean (value 2)? Problem states 4 is start, so no bean.

    // Simulation loop with safety cap
    for (int steps = 0; steps < 1000000; ++steps) {
        State st{r,c,dir};
        if (seen.find(st) != seen.end()) {
            cout << "Silly Pacman";
            return 0;
        }
        seen.insert(st);

        // Choose next move following right-hand rule
        array<int,4> pr = next_dir_priority(dir);
        bool moved = false;
        for (int nd : pr) {
            int nr = r + dr[nd];
            int nc = c + dc[nd];
            if (nr < 0 || nr >= 10 || nc < 0 || nc >= 10) continue; // outside treated as wall
            if (g[nr][nc] == 0) continue; // wall
            // move
            r = nr; c = nc; dir = nd; moved = true; break;
        }
        if (!moved) {
            // Surrounded by walls -> cannot move; then stuck would loop? Define as Silly Pacman as well
            cout << "Silly Pacman";
            return 0;
        }

        // Scoring after moving into cell
        if (g[r][c] == 3) {
            score -= 500;
            cout << score;
            return 0;
        }
        if (g[r][c] == 2) {
            score += 2;
            g[r][c] = 1; // consume bean
        }
    }

    // Safety fallback (should not happen). If exceeded steps, consider it a loop.
    cout << "Silly Pacman";
    return 0;
}
