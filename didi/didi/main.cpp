//
//  main.cpp
//  didi
//
//  Created by Jiahui Sun on 2018/11/8.
//  Copyright © 2018 Jiahui Sun. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int findKNum( vector<int>& src) {
    if(src.empty()) return 0;
    
    unordered_map<int, int> res;
    int maxK = 0;
    
    for(int i = 0; i < src.size(); i++) {
        res[src[i]]++;
    }
    
    for(auto element : res) {
        maxK = max(maxK, element.second);
    }
    
    return maxK;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> src = {1, 2, 3, 4, 4};
    cout << findKNum(src) << endl;
    return 0;
}
