#include <bits/stdc++.h>

using namespace std;

vector <vector<int>> commit;

int main() {

    vector <int> temp;

    temp.push_back(10);
    temp.push_back(20);
    temp.push_back(50);


    for(int k=0; k<temp.size(); ++k) {
        printf("%d ", temp[k]);
    }
    printf("\n");

    temp.clear();

    temp.push_back(100);
    temp.push_back(200);
    temp.push_back(500);

    for(int k=0; k<temp.size(); ++k) {
        printf("%d ", temp[k]);
    }

    return 0;
}
