#include <bits/stdc++.h>

using namespace std;

vector <vector <int>> G;
vector <vector <bool>> selected;
vector <bool> verticies;

map <string, int> commands{
        {"test", 1},
        {"print", 2},
        {"input", 3},
        {"prim", 4},
        {"close", 5}

};

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

void Test(){
    G = {
            {0, 9, 75, 0, 0},
            {9, 0, 95, 19, 42},
            {75, 95, 0, 51, 66},
            {0, 19, 51, 0, 31},
            {0, 42, 66, 31, 0}
    };
}

void PrintG(){
    if (G.empty()){
        cout << "Graph is empty\n\n";
        return;
    }
    cout << "Adjacency matrix:\n";
    for (int i = 0; i < G.size(); i++) {
        for (int j = 0; j < G.size(); j++)
            cout << G[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void Input(){
    G.clear();
    vector <int> temp;
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            temp.push_back(x);
        }
        G.push_back(temp);
        temp.clear();
    }
}

bool Check(){
    for (int i = 0; i < G.size(); i++) {
        if (G[i][i] != 0)
            return false;
        for (int j = 0; j < G.size(); j++) {
            if (G[i][j] != G[j][i])
                return false;
        }
    }
    return true;
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
    return true;
}

void PrimFindMST(){
    bool flag = true;
    int mini, minj;
    FindMin(mini, minj);
    selected[mini][minj] = selected[minj][mini] = verticies[mini] = verticies[minj] = true;
    while (flag) {
        cout << mini+1 << "-" << minj+1 << endl;
        flag = FindAdjMin(mini, minj);
        if (!selected[mini][minj])
            selected[mini][minj] = selected[minj][mini] = verticies[mini] = verticies[minj] = true;
        else
            G[mini][minj] = G[minj][mini] = 0;

    }
    cout << endl;
}

int main() {
    string command;

    while (cout << ">", cin >> command){

        switch(commands[command])
        {
            case 1:
            {
                Test();
                ClearSelected();
                PrintG();
                break;
            }

            case 2:
            {
                PrintG();
                break;
            }

            case 3:
            {
                Input();
                if (!Check())
                    cout << "Incorrect data\n\n";
                else
                    cout << endl;
                ClearSelected();
                break;
            }

            case 4:
            {
                PrimFindMST();
                ClearSelected();
                break;
            }

            case 5:
            {
                exit(0);
            }

            default:
            {
                cout << "Unknown command\n\n";
                break;
            }
        }
    }
    return 0;
}