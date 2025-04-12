#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>>& queries) {
        vector<int> arr(n, 0);
        vector<int> output;
        int prev_output_int = n - 1; // initial output before any queries
        int cur_output_int = 0;
        unordered_map<int, vector<vector<int>>> color_to_positions;
        color_to_positions[0].push_back({0, n - 1}); // stores indexes

        for (auto& query : queries) {
            int idx = query[0];
            int color = query[1];
            int orig_color = arr[idx];
            vector<vector<int>>& position_container = color_to_positions[orig_color];

            // find target subvector index
            int target_subvector_index = targetSubvectorIndex(position_container, idx);

            // remove split
            int remove_split_delta = split_remove(position_container, target_subvector_index, idx);
            cur_output_int = prev_output_int + remove_split_delta;

            output.push_back(cur_output_int);

            prev_output_int = cur_output_int;
        }

        return output;
    }

    int targetSubvectorIndex(vector<vector<int>>& position_container, int target) {
        int i = 0;
        while (i < position_container.size() && position_container[i][1] < target) {
            i++;
        }
        return i;
    }

    // NOTE: subvector_idx is the index of the subvector containing the target_pos
    // Ex: position_container = { {}, ..., {a, ..., target_pos, ..., b}, ... {}}
    //     position_container[subvector_idx] = {a, ..., target_pos, ..., b}
    //
    // return: (int) removal delta split
    int split_remove(vector<vector<int>>& position_container, int subvector_idx,  int target_pos) {
        vector<vector<int>> result_of_split; // which we push back into the container
        vector<int>& subvector = position_container[subvector_idx]; // target subvector THAT WE SPLIT!
        int output = -1 * (subvector[1] - subvector[0]); // contribution pre-split
        if (target_pos == subvector[0] && target_pos == subvector[1]) {
            ; // pass
        } else if (target_pos == subvector[0]) {
            result_of_split.push_back({target_pos + 1, subvector[1]});
        } else if (target_pos == subvector[1]) {
            result_of_split.push_back({subvector[0], target_pos - 1});
        } else {
            result_of_split.push_back({subvector[0], target_pos - 1});
            result_of_split.push_back({target_pos + 1, subvector[1]});
        }

        vector<vector<int>> new_container;
        int i = 0;
        while (i < position_container.size() && i < subvector_idx) { // all the preceeding subvectors before the current subvector that we split
            new_container.push_back(position_container[i]);
            i++;
        }
        // i now points to subvector we split, skip and populate with result_of_split, then push i and continue the rest
        for (auto& subvec : result_of_split) {
            output += subvec[1] - subvec[0];
            new_container.push_back(subvec);
        }
        i++;
        while (i < position_container.size()) { // all the subvectors after the current subvector that we split
            new_container.push_back(position_container[i]);
            i++;
        }

        position_container = new_container;

        return output;
    }

    int join_add(vector<vector<int>>& position_container, int target_pos) {
        // TODO: req: 1. find insert position for new color
        // 2. insert with logic:
        //     if prev contianer and equal to prev container end + 1 && next container and equal to next container begin - 1: res = {prev start, next end}
        //     if prev container and equal to prev container end + 1, res = {prev start, target}
        // BUG: *Think about how to properly populate the result array.

        int n = position_container.size();

        // Find insert position
        int i = 0;
        while (i < n && position_container[i][1] < target_pos) {
            // increment i while it's guaranteed that target_pos is ahead of the current subvector pointed to by i
            i++;
        }

        // Insert position is AFTER the subvector before the current index.
        vector<int> prev_subvector;
        if (i > 0) {
            prev_subvector = position_container[i - 1];
        }
        vector<int> next_subvector;
        if (i < n) {
            next_subvector = position_container[i];
        }

        // flags for when I start building new_container
        bool include_prev_subvector = true;
        bool include_next_subvector = true;

        vector<int> consolidation;
        if ((prev_subvector.size() != 0 && target_pos == prev_subvector[1] + 1) &&
            (next_subvector.size() != 0 && target_pos == next_subvector[0] - 1)) {

            consolidation = {prev_subvector[0], next_subvector[1]};
            include_prev_subvector = false;
            include_next_subvector = false;

        } else if (prev_subvector.size() != 0 && target_pos == prev_subvector[1] + 1) {
            consolidation = {prev_subvector[0], target_pos};
            // modify prev -> !include prev
            include_prev_subvector = false;
        } else if (next_subvector.size() != 0 && target_pos == next_subvector[0] - 1) {
            consolidation = {target_pos, next_subvector[1]};
            include_next_subvector = false;
        } else {
            consolidation = {target_pos, target_pos};
        }

        vector<vector<int>> new_container;
        // iterate until i - 1 
        j = 0;
        while (j < i - 1) {
            new_container.push_back(position_container[i]);
        }

    }
};

int main() {
    Solution sol;
    int n = 5;
    // vector<vector<int>> queries = {{0,2},{1,2},{3,1},{1,1},{2,1}};
    vector<vector<int>> queries = {{2,5}};
    vector<int> output = sol.colorTheArray(n, queries);
    for (auto& o : output) {
        cout << o << endl;
    }
    return 0;
}
