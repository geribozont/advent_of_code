#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int easy_01(vector<string> data) {
    int position = 50;
    int counter = 0;

    for (const string& s : data){
        int step = stoi(s.substr(1));

        // Update position based on direction
        if (s[0] == 'L') position -= step;
        else             position += step;

        // Check if the landing position hits a boundary (multiples of 100)
        if (position % 100 == 0) 
            counter++;

        // Normalize position to [0, 99] using a safe modulo operation
        position = ((position % 100) + 100) % 100;
    }
    return counter;
}

int hard_01(vector<string> data){
    
    int position = 50;
    int counter = 0;
    for (const string& s : data){
        
        int n = stoi(s.substr(1));
        char direction = s[0];

        // Individual step simulation
        for (int i = 0; i < n; i++) {

            if (direction == 'L') {
                position--;
                if(position < 0) position = 99;
            }
            else{ 
                position++;
                if(position > 100) position = 1;
            }

            // Count every time we hit a boundary during the movement
            if (position == 0 || position == 100) 
                counter++;
        }
    }
    return counter;
}

int main(){

    ifstream input("01.txt");
    if (!input.is_open()) {
        cerr << "Could not open 01.txt." << endl;
        return 1;
    }

    vector<string> rows;
    string text;
    while (getline(input, text)) {
        if (!text.empty()) rows.push_back(text);
    }
    input.close();

    cout << "Easy: " << easy_01(rows) << endl;
    cout << "Hard: " << hard_01(rows) << endl;

    return 0;
}
