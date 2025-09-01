
#include <iostream>
#include <vector>

using namespace std;

class Solution { // https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/submissions/1755423285
public:
    int maxProfit(vector<int>& prices) {
        int accumulator = 0;
        
        int cur = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > cur)
                accumulator += prices[i] - cur;
            cur = prices[i];
        }

        return accumulator;
    }
};

int main(void) {

    return 0;
}
