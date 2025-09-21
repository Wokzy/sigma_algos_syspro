#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_set>

using namespace std;

// https://leetcode.com/problems/redundant-connection/submissions/1770138208
// https://leetcode.com/problems/redundant-connection-ii/submissions/1770159551

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();

        vector<int> parents(n + 1, 0);

        bool flag = false;
        vector<int> double_parent1 = {};
        vector<int> double_parent2 = {};

        vector<int> disjoint_set(n, 0);
        vector<vector<int>> colors_info(n);

        for (int i = 0; i < n; i++) {
            disjoint_set[i] = i;
            colors_info[i].push_back(i);

            if (parents[edges[i][1]]) {
                double_parent1 = edges[i];
                double_parent2 = {parents[edges[i][1]], edges[i][1]};
                flag = true;
            } else {
                parents[edges[i][1]] = edges[i][0];
            }
        }

        for (int i = 0; i < n; i++) {
            if (flag && (edges[i][0] == double_parent1[0] && edges[i][1] == double_parent1[1]))
                continue;

            int color1 = disjoint_set[edges[i][0] - 1];
            int color2 = disjoint_set[edges[i][1] - 1];
            if (color1 == color2){
                if (flag)
                    return double_parent2;
                return edges[i];
            }

            if (colors_info[color1].size() < colors_info[color2].size()) {
                for (int& c : colors_info[color1]) {
                    disjoint_set[c] = color2;
                    colors_info[color2].push_back(c);
                }
                colors_info[color1].clear();
            } else {
                for (int& c : colors_info[color2]) {
                    disjoint_set[c] = color1;
                    colors_info[color1].push_back(c);
                }
                colors_info[color2].clear();
            }
        }

        return double_parent1;
    }
};

