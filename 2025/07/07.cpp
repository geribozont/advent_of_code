#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void print(vector<string> &rows){
    for(int i=0; i<rows.size(); ++i){
        for(int j=0; j<rows[i].size(); ++j){
            cout << rows[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void print_road(vector<vector<long>> &rows){
    for(int i=0; i<rows.size(); ++i){
        for(int j=0; j<rows[i].size(); ++j){
            cout << rows[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

long easy(vector<string> &rows){

    long result = 0;
    vector<pair<int,int>> beams;

    for(int j=0; j<rows[0].size(); ++j){
        if(rows[0][j] == 'S'){
            rows[1][j] = '|';
            pair<int,int> newcoord;
            newcoord.first = 1;
            newcoord.second = j;
            beams.push_back(newcoord);
        }
    }

    for(int i=1; i<rows.size(); ++i){
        for(int j=0; j<rows[i].size(); ++j){
            if(rows[i-1][j] == '|' && rows[i][j] == '.'){
                rows[i][j] = '|';
                pair<int,int> newcoord;
                newcoord.first = i+1;
                newcoord.second = j;
                beams.push_back(newcoord);
            }
            if(rows[i][j] == '^' && rows[i-1][j] == '|'){
                pair<int,int> newcoord;
                rows[i][j+1] = '|';
                newcoord.first = i;
                newcoord.second = j+1;
                beams.push_back(newcoord);
                rows[i][j-1] = '|';
                newcoord.second = j-1;
                beams.push_back(newcoord);
                result++;
            }
        }
        //print(rows);
    }

    cout << "Result easy: " << result << endl;

    // End of easy

    vector<vector<long>> roads;
    vector<long> road;
    for(int j=0; j<rows[0].size(); ++j) road.push_back(0);
    road[beams[0].second] = 1;
    roads.push_back(road);
    road.clear();

    for(int i=1; i<rows.size(); ++i){
        for(int j=0; j<rows[i].size(); ++j){

            if(rows[i][j] == '|' || rows[i][j] == 'S'){

                long value = 0;
                char valami = rows[i-1][j];

                if(rows[i-1][j] == '|' || rows[i-1][j] == 'S') { value += roads[i-1][j]; }
                if(rows[i][j-1] == '^') { value += roads[i-1][j-1]; }
                if(rows[i][j+1] == '^') { value += roads[i-1][j+1]; }
                
                road.push_back(value);

                if (value < 0){
                    cout << "breakpoint";
                }
            
            } else if(rows[i][j] == '|'){ road.push_back(0); }

            else road.push_back(0);

        }
        result = 0;
        if(i == rows.size()-1){
            for(long num : road){
                result += num;
            }
        }
        roads.push_back(road);
        road.clear();
    }

    //print_road(roads);
    return result;
}

int main()
{
    ifstream input;
    vector<string> rows;
    string text;
    input.open("07.txt");
    long answer = 0;
    while (getline(input, text))
    {
        rows.push_back(text);
    }
    answer = easy(rows);
    cout << "Result hard: "<< answer << endl;
    input.close();
    return 0;
}
