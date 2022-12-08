#include<iostream>
//#include<algorithm>
#include<vector>
//#include <tuple>
#include <string>
//#include <iterator>
//#include <map>
//#include <unordered_set>

using namespace std;
int MathChallenge(string str) {

    vector<int> v;
    int NextNumFlag = 0;
    for (int idx = 0; idx < str.size(); idx++) {
        if (str[idx] == '+') {
            v[v.size() - 2] = v[v.size() - 2] + v[v.size() - 1];
            v.pop_back();
            NextNumFlag = 0;
        }
        else if (str[idx] == '-') {
            v[v.size() - 2] = v[v.size() - 2] - v[v.size() - 1];
            v.pop_back();
            NextNumFlag = 0;
        }
        else if (str[idx] == '*') {
            v[v.size() - 2] = v[v.size() - 2] * v[v.size() - 1];
            v.pop_back();
            NextNumFlag = 0;
        }
        else if (str[idx] == '/') {
            v[v.size() - 2] = v[v.size() - 2] / v[v.size() - 1];
            v.pop_back();
            NextNumFlag = 0;
        }
        else if (NextNumFlag == 1 && str[idx] != ' ') { //next idx is not space then
            int tmpnum = v[v.size() - 1] * 10 + str[idx] - '0';
            v[v.size() - 1] = tmpnum;
        }
        else {//first digit
            if (str[idx] != ' ') {
                v.push_back(str[idx] - '0');
                NextNumFlag = 1;
            }
            else {
                NextNumFlag = 0;
            }

        }
    }

    // code goes here  
    return v.front();

}

int main(void) {

    // keep this function call here
    cout << MathChallenge("2 13 + 7 /");
    return 0;

}