#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

long hard(vector<string> &rows){
    long result = 0;
    vector<long> numbers;
    for(int i = rows[0].size()-1; i>=0;--i){
        string number = "";
        for(int j = 0; j<rows.size()-1; ++j){
            char ch = rows[j][i];
            if(rows[j][i] != ' '){
                number.push_back(rows[j][i]);
            }
        }
        if (!number.empty()) numbers.push_back(stol(number));
        number.clear();
        if(rows[rows.size()-1][i] == '*'){
            long reszmegoldas = 1;
            for(long num : numbers){
                reszmegoldas *= num;
            }
            result += reszmegoldas;
            numbers.clear();
        }
        if(rows[rows.size()-1][i] == '+'){
            long reszmegoldas = 0;
            for(long num : numbers){
                reszmegoldas += num;
            }
            result += reszmegoldas;
            numbers.clear();
        }
    }
    return result;
}

long easy(vector<string> rows){
    long result = 0;
    vector<vector<long>> numbers;

    for(int i=0; i<4; ++i){
        string number = "";
        vector<long> rownumber;
        for(int j=0; j<rows[i].size(); ++j){
            char ch = rows[i][j];
            
            if(ch == ' ' && !number.empty()){
                rownumber.push_back(stol(number));
                number.clear();
            } else if(ch != ' '){
                number.push_back(ch);
            }
        }
        if(!number.empty()){
            rownumber.push_back(stol(number));
            number.clear();
        }
        numbers.push_back(rownumber);
    }
    vector<char> operators;
    for(int i=0;i<rows[4].size();++i){
        if(rows[4][i] != ' ') operators.push_back(rows[4][i]);
    }
    
    for(int i=0;i<numbers[0].size();++i){
        if(operators[i] == '*'){
            result += numbers[0][i] * numbers[1][i] * numbers[2][i] * numbers[3][i];
        }else if(operators[i] == '+'){
            result += numbers[0][i] + numbers[1][i] + numbers[2][i] + numbers[3][i];
        }
    }

    return result;
}

int main()
{
    ifstream input;
    vector<string> rows;
    string text;
    input.open("06.txt");
    long answer = 0;
    while (getline(input, text))
    {
        rows.push_back(text);
    }
    answer = easy(rows);
    cout << "Easy: " << answer << endl;
    answer = hard(rows);
    cout << "Hard: " << answer << endl;
    input.close();
    return 0;
}
