#include <array>
#include <iostream>
#include <set>

#include "AOC_Solver.h"

using ScannerView = std::set<std::tuple<int, int, int>>;
using DeltaView = std::vector<std::array<int, 3>>;

std::vector<ScannerView> loadInput(std::vector<std::string>& input) {
    std::vector<ScannerView> scanners;
    ScannerView view;
    for (auto& line : input) {
        if (line.size() < 2) {
            scanners.push_back(view);
            view.clear();
        }
        else if (line[1] != '-') {
            int x, y, z;
            sscanf_s(line.c_str(), "%d,%d,%d\n", &x, &y, &z);
            view.insert({ x, y, z });
        }
    }
    scanners.push_back(view);
    return scanners;
}

std::array<int, 3> setDeltas(const ScannerView& view, const std::array<int, 3>& point, DeltaView& delta, int rx, int ry, int rz, int sx, int sy, int sz) {
    delta.clear();
    for (const auto& [x, y, z] : view) {
        std::array<int, 3> coord = { x, y, z };
        delta.push_back({ sx * (coord[rx] - point[rx]), sy * (coord[ry] - point[ry]), sz * (coord[rz] - point[rz]) });
    }
    return { -sx * point[rx], -sy * point[ry], -sz * point[rz] };
}

bool tryAndMerge(ScannerView& map, const ScannerView& view, std::vector<std::array<int, 3>>& positions) {
    if (map.empty()) {
        for (const auto& p : view)
            map.insert(p);
        positions.push_back({ 0, 0, 0 });
        return true;
    }

    //  [facing, up, right, sign_f, sign_u, sign_r]
    std::vector<std::tuple<int, int, int, int, int, int>> axis = {
        {0, 1, 2, 1, 1, 1},    //  x  y  z
        {0, 1, 2, 1, -1, -1},  //  x -y -z
        {0, 2, 1, 1, 1, -1},   //  x  z -y
        {0, 2, 1, 1, -1, 1},   //  x -z  y
        {0, 1, 2, -1, 1, -1},  // -x  y -z
        {0, 1, 2, -1, -1, 1},  // -x -y  z
        {0, 2, 1, -1, 1, 1},   // -x  z  y
        {0, 2, 1, -1, -1, -1}, // -x -z -y
    };

    std::vector<std::tuple<int, int, int, int, int, int>> rot;
    for (int a = 0; a < 3; a++)
        for (const auto& [dx, dy, dz, sx, sy, sz] : axis)
            rot.push_back({ (a + dx) % 3, (a + dy) % 3, (a + dz) % 3, sx, sy, sz });

    DeltaView delta;
    for (const auto& [px, py, pz] : view) {
        for (const auto& [rx, ry, rz, sx, sy, sz] : rot) {
            auto sp = setDeltas(view, { px, py, pz }, delta, rx, ry, rz, sx, sy, sz);
            for (const auto& [x, y, z] : map) {
                int matches = 0;
                for (const auto& d : delta)
                    matches += (map.count({ d[0] + x, d[1] + y, d[2] + z }));

                if (matches >= 12) { //Merge
                    for (const auto& d : delta)
                        map.insert({ d[0] + x, d[1] + y, d[2] + z });
                    positions.push_back({ sp[0] + x, sp[1] + y, sp[2] + z });
                    return true;
                }
            }
        }
    }
    return false;
}

uint64_t aoc::day19::part_1(std::vector<std::string>& input) {
    auto scanners = loadInput(input);
    ScannerView map;

    std::set<int> remaining;
    for (int i = 0; i < scanners.size(); i++)
        remaining.insert(i);

    std::vector<std::array<int, 3>> sp;

    while (!remaining.empty())
        for (int i = 0; i < scanners.size(); i++)
            if (remaining.count(i) && tryAndMerge(map, scanners[i], sp))
                remaining.erase(i);

    int mm = 0;
    for (int i = 0; i < sp.size(); i++)
        for (int j = 0; j < sp.size(); j++)
            mm = std::max(std::abs(sp[i][0] - sp[j][0]) + std::abs(sp[i][1] - sp[j][1]) + std::abs(sp[i][2] - sp[j][2]), mm);
    
	return map.size();
}

uint64_t aoc::day19::part_2(std::vector<std::string>& input) {
    auto scanners = loadInput(input);
    ScannerView map;

    std::set<int> remaining;
    for (int i = 0; i < scanners.size(); i++)
        remaining.insert(i);

    std::vector<std::array<int, 3>> sp;

    while (!remaining.empty())
        for (int i = 0; i < scanners.size(); i++)
            if (remaining.count(i) && tryAndMerge(map, scanners[i], sp))
                remaining.erase(i);

    int mm = 0;
    for (int i = 0; i < sp.size(); i++)
        for (int j = 0; j < sp.size(); j++)
            mm = std::max(std::abs(sp[i][0] - sp[j][0]) + std::abs(sp[i][1] - sp[j][1]) + std::abs(sp[i][2] - sp[j][2]), mm);
    
	return mm;
}