#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void print_vector(vector<vector<char>> &data){
    for (int i = 0; i < data.size(); ++i){
        for (int j = 0; j < data[0].size(); ++j)
            cout << data[i][j];
        cout << endl;
    }
}

vector<vector<char>> prepare_data(vector<string> &data){

    vector<vector<char>> new_data;
    for (int i = 0; i < data.size(); ++i){

        vector<char> new_data_row;
        for (int j = 0; j < data[0].size(); ++j)
            new_data_row.push_back(data[i][j]);
        
        new_data.push_back(new_data_row);
    }
    return new_data;
}

vector<vector<char>> removel_rolls(vector<vector<char>> &data, int &removed_roll, int &result_hard){

    removed_roll = 0;
    vector<vector<char>> new_data;

    // first row
    vector<char> new_row;
    for (int i = 0; i < data[0].size() + 2; ++i)
        new_row.push_back('.');

    new_data.push_back(new_row);
    new_row.clear();

    // other rows
    for (size_t i = 0; i < data.size(); ++i){
        new_row.push_back('.');
        for (size_t j = 0; j < data[0].size(); ++j)
        {
            new_row.push_back(data[i][j]);
        }
        new_row.push_back('.');
        new_data.push_back(new_row);
        new_row.clear();
    }

    // last row
    for (int i = 0; i < data[0].size() + 2; ++i)
        new_row.push_back('.');

    new_data.push_back(new_row);
    new_row.clear();

    vector<vector<char>> num_data; // this return
    vector<char> num_data_row;

    for (size_t i = 0; i < data.size(); ++i){
        for (size_t j = 0; j < data[0].size(); ++j){
            if (new_data[i + 1][j + 1] == '@'){

                int number = 0;
                for (size_t inner_i = i; inner_i <= i + 2; ++inner_i){

                    for (size_t inner_j = j; inner_j <= j + 2; ++inner_j){
                        if (new_data[inner_i][inner_j] == '@')
                            number++;
                    }
                }

                if (number - 1 < 4){
                    result_hard++;
                    removed_roll++;
                    num_data_row.push_back('.');
                }
                else{
                    num_data_row.push_back('@');
                }

            }

            if (new_data[i + 1][j + 1] == '.'){
                num_data_row.push_back('.');
            }
        }

        num_data.push_back(num_data_row);
        num_data_row.clear();
    }

    //print_vector(num_data);
    cout << "removed_rolls: " << removed_roll << endl;

    return num_data;
}

int easy_04(vector<string> &data){

    vector<vector<char>> in_data = prepare_data(data);

    int removed_rolls = 1;
    int result_hard = 0;

    while (removed_rolls != 0){
        in_data = removel_rolls(in_data, removed_rolls, result_hard);
        cout << removed_rolls << endl;
    }

    cout << "Result part 2: " << result_hard << endl;
    return 0;
}

int main()
{

    ifstream input;
    vector<string> rows;
    string text;
    input.open("04.txt");
    int answer = 0;
    while (getline(input, text))
    {
        rows.push_back(text);
    }
    answer = easy_04(rows);
    input.close();
    return 0;
}
