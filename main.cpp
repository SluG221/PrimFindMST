#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

vector <vector <int>> G;
vector <vector <bool>> selected;
vector <bool> verticies;
vector <int> answer;

int sum = 0;

void ClearSelected(){
    verticies.clear();
    selected.clear();
    vector <bool> temp;
    for (int i = 0; i < G.size(); i++) {
        verticies.push_back(false);
        for (int j = 0; j < G.size(); j++) {
            temp.push_back(false);
        }
        selected.push_back(temp);
        temp.clear();
    }
}

void FindMin(int &mini, int &minj){
    int min = INFINITY;
    for (int i = 0; i < G.size(); i++){
        for (int j = 0; j < G.size(); j++){
            if (G[i][j] != 0 && G[i][j] < min){
                min = G[i][j];
                mini = i;
                minj = j;
            }
        }
    }
    sum += min;
}

bool FindAdjMin(int &mini, int &minj){
    int mini2 = mini, minj2 = minj;
    int min = INFINITY;

    for (int i = 0; i < G.size(); i++){
        if (verticies[i]){
            for (int j = 0; j < G.size(); j++){
                if (!selected[i][j] && !verticies[j] && G[i][j] < min && G[i][j] != 0){
                    min = G[i][j];
                    mini2 = i;
                    minj2 = j;
                }
            }
        }
    }

    if (mini == mini2 && minj == minj2)
        return false;
    mini = mini2;
    minj = minj2;
    sum += min;
    return true;
}

void PrimFindMST(){
    ClearSelected();
    bool flag = true;
    int mini, minj;
    FindMin(mini, minj);
    selected[mini][minj] = selected[minj][mini] = verticies[mini] = verticies[minj] = true;
    while (flag) {
        answer.push_back(min(mini+1, minj+1));
        answer.push_back(max(mini+1, minj+1));
        flag = FindAdjMin(mini, minj);
        if (!selected[mini][minj])
            selected[mini][minj] = selected[minj][mini] = verticies[mini] = verticies[minj] = true;
        else
            G[mini][minj] = G[minj][mini] = 0;

    }
    cout << endl;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n;
    fin >> n;
    vector <int> temp;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            string x;
            fin >> x;
            if (x == "~")
                temp.push_back(0);
            else
                temp.push_back(stoi(x));
        }
        G.push_back(temp);
        temp.clear();
    }
    PrimFindMST();
    fout << sum << endl;
    for (int i = 0; i < answer.size(); i+=2){
        fout << answer[i]<< " " << answer[i+1] << endl;
    }
    return 0;
}