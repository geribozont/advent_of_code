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

bool check_good_squeare(SquareSize &s, vector<Point> &points){

    int square_minX = min(s.p1.X, s.p2.X);
        int square_maxX = max(s.p1.X, s.p2.X);
        int square_minY = min(s.p1.Y, s.p2.Y);
        int square_maxY = max(s.p1.Y, s.p2.Y);


    for(int j = 0; j < points.size(); ++j){
            int l = (j+1==points.size()) ? 0 : j+1;
            int d_X = (points[j].X >= points[l].X) ? -1 : 1;
            int d_Y = (points[j].Y >= points[l].Y) ? -1 : 1;
            for(int y = points[j].Y; y != points[l].Y+d_Y; y+=d_Y){
                for(int x = points[j].X; x != points[l].X+d_X; x+=d_X){
                    if(x > square_minX && x < square_maxX && y > square_minY && y < square_maxY){
                        return false;
                    }
                }
            }
        }
    return true;
}

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

    vector<SquareSize> uniqueDistancesGood;

    for(auto it = uniqueDistances.rbegin(); it != uniqueDistances.rend(); ++it){
        SquareSize s = *it;
        int square_minX = min(s.p1.X, s.p2.X);
        int square_maxX = max(s.p1.X, s.p2.X);
        int square_minY = min(s.p1.Y, s.p2.Y);
        int square_maxY = max(s.p1.Y, s.p2.Y);

        if(check_good_squeare(s, points)){
            return s.dist;
        }

    }

    return 0;    
}

int main()
{
    ifstream input;
    vector<string> rows;
    string text;
    input.open("09_mini.txt");
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
