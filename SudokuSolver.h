#ifndef _SUDOKUSOLVER_H_
#define _SUDOKUSOLVER_H_

#define FOR(i,n) for(int i = 0; i < n; i++)


#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
using namespace std;


enum unit_type {row, col, box};

class SudokuSolver {
private:
const size_t BOX_WD = 3;
const size_t BOX_HT = 3;
const size_t LEN = BOX_WD*BOX_HT;
vector<vector<set<int>>> cands;
vector<vector<int>> board;

public:
SudokuSolver(const string& filename);
void solve();
friend std::ostream& operator<< (std::ostream& stream, const SudokuSolver& s) {
    for(auto & row : s.board) {
        for (int c : row) stream<<c<<" ";
        stream<<"\n";
    }

    vector<vector<int>> v(s.LEN*s.BOX_WD, vector<int>(s.LEN*s.BOX_HT,0));
    FOR(i,s.LEN) {
        FOR(j,s.LEN) {
            FOR(k,s.LEN) {
                int num = (s.cands[i][j].count(k+1) ? k+1 : 0);
                int ti = i*s.BOX_HT + k/s.BOX_HT;
                int tj = j*s.BOX_WD + k%s.BOX_WD;
                v[ti][tj] = num;
            }
        }
    }

    FOR(i,v.size()) {
        FOR(j,v[0].size()) {
            if(v[i][j]==0) stream<<" ";
            else stream<<v[i][j];
            if(j%s.BOX_WD==s.BOX_WD-1) stream<<"\t";
        }
        stream<<"\n";
        if(i%s.BOX_HT==s.BOX_HT-1) stream<<"\n";
    }
    return stream;
} 


private:
void fill_candidates(); //called in init
bool check_union_is_bipartite(const vector<int> &);
void reduce_candidates(unit_type, int, int, const set<int>&);
void set_diff(set<int>& , const set<int>&);
};

#endif