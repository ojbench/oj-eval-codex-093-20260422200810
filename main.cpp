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

    // State for loop detection: position + direction + remaining beans pattern matters for scoring repeat?
    // But requirement: if Pacman would enter a dead loop (movement repeats), output "Silly Pacman".
    // Beans are consumed; however loop definition likely means movement cycles without hitting ghost,
    // regardless of beans state. To be robust, track (r,c,dir) visited count after beans stop changing.
    // Simpler: track full state (r,c,dir) and the set of eaten beans could be large. Instead,
    // as beans are finite, once a state repeats (r,c,dir) with the same grid beans configuration, it's a cycle.
    // Encoding full grid is heavy; but 10x10 small -> we can hash the grid's bean positions (value 2 means uneaten).

    auto hash_grid = [&](const vector<vector<int>>& grid)->uint64_t{
        uint64_t h = 1469598103934665603ull;
        const uint64_t FNV_PRIME = 1099511628211ull;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                // Only bean presence affects future scoring; walls/empty/ghosts/static don't change
                unsigned char v = (grid[i][j] == 2);
                h ^= v;
                h *= FNV_PRIME;
            }
        }
        return h;
    };

    unordered_set<uint64_t> seen;
    seen.reserve(1<<12);

    auto state_key = [&](int rr,int cc,int d)->uint64_t{
        uint64_t h = hash_grid(g);
        h ^= (uint64_t)(rr*10+cc) + 0x9e3779b97f4a7c15ull + (h<<6) + (h>>2);
        h ^= (uint64_t)d * 0xbf58476d1ce4e5b9ull;
        return h;
    };

    // If starting on a bean (value 2)? Problem states 4 is start, so no bean.

    // Simulation loop with safety cap
    for (int steps = 0; steps < 1000000; ++steps) {
        uint64_t key = state_key(r,c,dir);
        if (seen.find(key) != seen.end()) {
            cout << "Silly Pacman";
            return 0;
        }
        seen.insert(key);

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

