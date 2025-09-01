#include <iostream>
#include <vector>

using namespace std;

class Solution { // https://leetcode.com/problems/jump-game/submissions/1755391890
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() == 1)
            return true;

        int cur_index = nums.size() - 1;

        for (int i = nums.size() - 2; i >= 0; i--) {
            if (cur_index - i <= nums[i])
                cur_index = i;

            if (cur_index == 0)
                return true;
        }

        return false;
    }
};

int main(void) {
    Solution sol = Solution();

    return 0;
}
