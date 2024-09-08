// enum unit_type {row, col, box};

// class SudokuSolver {
// private:
// const int LEN = 9;
// vector<vector<set<int>>> board;

#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(const string& fileName) {
    ifstream fin;
    try {   
        fin.open(fileName);
    } catch (std::ios_base::failure& e) {
        std::cerr << e.what() << '\n';
    }
    string row;
    int rownum = 1;
    while(getline(fin,row)) {
        if(row.size()!=LEN) {
            std::cerr<<"Row "<<rownum<<" has incorrect number of characters" <<'\n';
            exit(1);
        }
        board.push_back({});
        for(char c : row) {
            if(c >= '1' && c<='9') c -= '0';
            else c = 0;
            board.back().push_back((int)c);
        }
        rownum++;
    }
    if(rownum-1!=LEN) {
        std::cerr<<"has incorrect number of rows" <<'\n';
        exit(1);
    }
    fill_candidates();
}
void SudokuSolver::solve() {

}
//called in init
void SudokuSolver::fill_candidates() {
    
    //fill in all numbers in every box
    set<int> numbers;
    FOR(i,LEN) numbers.insert(i+1);
    cands.resize(LEN,vector<set<int>>(LEN,numbers));

    //erase the numbers 
    FOR(i,LEN) {
        FOR(j,LEN) {
            if(board[i][j]!=0) {
                reduce_candidates(unit_type::row,i,j, {board[i][j]});
                reduce_candidates(unit_type::col,i,j, {board[i][j]});
                reduce_candidates(unit_type::box,i,j, {board[i][j]});
            }
        }
    }    
} 
bool SudokuSolver::check_union_is_bipartite(const vector<int> &) {
    return false;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for (const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}

void SudokuSolver::reduce_candidates(unit_type ut, int r, int c, const set<int>& nums) {
    
    switch (ut)
    {
    case row:
        FOR(j,LEN) {
            if(j==c) continue;
            set_diff(cands[r][j],nums);
        }
        break;
    case col:
        FOR(i,LEN) {
            if(i==r) continue;
            set_diff(cands[i][c],nums);
        }
        break;
    case box:
        // FOR(i,BOX_HT) {
        //     FOR(j,BOX_WD) {
        //         int ti = r*BOX_HT + i;
        //         int tj = c*BOX_WD + j;
        //         if(i*BOX_HT+j==)
        //     }
        // }
        break;
    
    default:
        break;
    }
}
void SudokuSolver::set_diff(set<int>& s1, const set<int>& s2) {
    for(int e : s2) s1.erase(e);
}
int main() {
    SudokuSolver ss("input.txt");
    cout<<ss<<endl;
}