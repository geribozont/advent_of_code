#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <set>

using namespace std;

struct Point{
    int X, Y;

};

struct SquareSize{
    long long dist;
    Point p1, p2;
    bool operator < (const SquareSize& s) const{
        return dist < s.dist;
    }
};

long long solver(vector<string> &rows){

    vector<Point> points;
    for(int i=0; i<rows.size(); ++i){
        vector<int> numbers;
        string number = "";
        for(int j=0; j<rows[i].size(); ++j){
            if(rows[i][j] == ','){
                numbers.push_back(stoi(number));
                number.clear();
            } else{
                number.push_back(rows[i][j]);
            }
        }
        numbers.push_back(stoi(number));
        number.clear();
        Point p;
        p.X = numbers[0];
        p.Y = numbers[1];
        points.push_back(p);
        numbers.clear();
    }

    multiset<SquareSize> uniqueDistances;
    for(int i = 0; i < points.size(); ++i){
        for(int j = i+1; j < points.size(); ++j){
            SquareSize s;
            long long asd = abs(points[i].X-points[j].X)+1;
            long long asf = abs(points[i].Y-points[j].Y)+1;
            s.dist = asd * asf;
            s.p1 = points[i];
            s.p2 = points[j];
            uniqueDistances.insert(s);
        }
    }
    // For easy
    //return (--uniqueDistances.end())->dist;

    cout << "Unique distances: " << uniqueDistances.size() << endl;

    
    return 0;
    
}

int main()
{
    ifstream input;
    vector<string> rows;
    string text;
    input.open("09.txt");
    long long answer = 0;
    while (getline(input, text))
    {
        rows.push_back(text);
    }
    answer = solver(rows);
    cout << "Answer: " << answer << endl;
    input.close();
    return 0;
}
