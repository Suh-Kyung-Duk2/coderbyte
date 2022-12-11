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
        else if (NextNumFlag == 1 && str[idx] != ' ') { //for"1""2", if "1" next is not space then make "12"
            int tmpnum = v[v.size() - 1] * 10 + str[idx] - '0';
            v[v.size() - 1] = tmpnum;
        }
        else {//first digit
            if (str[idx] != ' ') {
                v.push_back(str[idx] - '0');
                NextNumFlag = 1;//Flag used in order to make "1""2"->"12"
            }
            else {
                NextNumFlag = 0;//if it is just space
            }

        }
    }
    return v.front();
}


int main(void) {

    // keep this function call here
    cout << MathChallenge("2 12 + 7 /");
    return 0;

}