#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int easy_03(vector<string> data){

    int result = 0;

    for (size_t i=0; i<data.size(); ++i){

        int first_digit, second_digit, pos_first_digit, pos_second_digit;
        int max_digit_first = 0;
        int max_digit_second = 0;

        for(size_t j = 0; j < data[i].size() - 1; ++j){
            int current = data[i][j] - '0';
            if(current > max_digit_first) {
                max_digit_first = current;
                pos_first_digit = j;
            }
        }

        for(size_t j = pos_first_digit; j < data[i].size(); ++j){
            int current = data[i][j] - '0';
            if(current > max_digit_second && j != pos_first_digit) {
                max_digit_second = current;
                pos_second_digit = j;
            }
        }
        result += max_digit_first*10 + max_digit_second;
    }

    return result;
}

long hard_03(vector<string> &data){

    long result = 0;
    for (size_t i=0; i<data.size(); ++i){

        int pos_last_number = -1;
        string result_string = "";
        for(int j = 11; j>=0; --j){
            
            int max_number = 0;

            for(int k = pos_last_number + 1; k < data[i].size()-j; ++k){

                int current_num = data[i][k] - '0';
                if(current_num > max_number){
                    max_number = current_num;
                    pos_last_number = k;
                }
                
            }
            result_string.push_back(data[i][pos_last_number]);

        }
        result += stol(result_string);

    }

    return result;
}

int main(){

    ifstream input;
    vector<string> rows;
    string text;
    input.open("03.txt");
    long answer = 0;
    while (getline (input, text)){
        rows.push_back(text);
    }
    answer = easy_03(rows);
    cout << "Easy: " << answer << endl;
    answer = hard_03(rows);
    cout << "Hard: " << answer << endl;
    input.close();
    return 0;
}

