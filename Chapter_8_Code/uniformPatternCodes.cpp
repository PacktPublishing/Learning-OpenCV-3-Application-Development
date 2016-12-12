#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> convertToBinary(int x) {
    vector<int> result(8, 0);
    
    int idx = 0;
    while(x != 0) {
        result[idx] = x % 2;
        ++idx;
        x /= 2;
    }

    reverse(result.begin(), result.end());
    return result;
}

int countTransitions(vector<int> x) {
    int result = 0;
    for(int i = 0; i < 8; ++i)
        result += (x[i] != x[(i+1) % 8]);
    return result;
}

int main() {

    int uniform_pattern_cnt = 0;
    for (int i = 0; i < 256; ++i) {
        vector<int> bin_i = convertToBinary(i);
        int num_transitions = countTransitions(bin_i);
        
        if (num_transitions <= 2)
            uniform_pattern_cnt += 1;
    }

    cout << "There are " << uniform_pattern_cnt << " 8-bit uniform patterns\n";

    return 0;
}
