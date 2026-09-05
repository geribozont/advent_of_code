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

vector<vector<bool>> grid_builder(vector<Point> &points){
    int maxX = points[0].X;
    int maxY = points[0].Y;

    for(int i = 1; i < points.size(); ++i){
        if(points[i].X > maxX) maxX = points[i].X;
        if(points[i].Y > maxY) maxY = points[i].Y;
    }

    vector<vector<bool>> grid(maxY+2, vector<bool>(maxX+2, false));
    for(int y = 0; y <= maxY+1; ++y){
        for(int x = 0; x <= maxX+1; ++x){
            bool found = false;
            for(int i = 0; i < points.size(); ++i){
                if(points[i].X == x && points[i].Y == y){
                    found = true;
                    break;
                }
            }
            if(found){
                grid[y][x] = true;
            }
        }
    }

    for(int p1 = 0; p1 < points.size()-1; ++p1){
        
        // Draw lines between points
        if(points[p1].X == points[p1+1].X){
            // Vertical line
            int x = points[p1].X;
            int y1 = points[p1].Y;
            int y2 = points[p1+1].Y;
            if(y1 > y2) swap(y1, y2);
            for(int y = y1; y <= y2; ++y){
                grid[y][x] = true;
            }
        } else if(points[p1].Y == points[p1+1].Y){
            // Horizontal line
            int y = points[p1].Y;
            int x1 = points[p1].X;
            int x2 = points[p1+1].X;
            if(x1 > x2) swap(x1, x2);
            for(int x = x1; x <= x2; ++x){
                grid[y][x] = true;
            }
        }

        // Connect last point to first point to close the shape
        if(p1 == points.size()-2){
            if(points[p1+1].X == points[0].X){
                // Vertical line
                int x = points[p1+1].X;
                int y1 = points[p1+1].Y;
                int y2 = points[0].Y;
                if(y1 > y2) swap(y1, y2);
                for(int y = y1; y <= y2; ++y){
                    grid[y][x] = true;
                }
            }
            else if(points[p1+1].Y == points[0].Y){
                // Horizontal line
                int y = points[p1+1].Y;
                int x1 = points[p1+1].X;
                int x2 = points[0].X;
                if(x1 > x2) swap(x1, x2);
                for(int x = x1; x <= x2; ++x){
                    grid[y][x] = true;
                }
            }
        }



    }

    // Fill the shape with a different character
    for(int y = 0; y <= maxY+1; ++y){
        for(int x = 0; x <= maxX+1; ++x){
            if(grid[y][x] == false){
                // Check if the point is inside the shape using ray-casting algorithm
                int intersections = 0;
                for(int i = 0; i < points.size(); ++i){
                    Point p1 = points[i];
                    Point p2 = points[(i+1) % points.size()];
                    if((p1.Y > y) != (p2.Y > y)){
                        double slope = (double)(p2.X - p1.X) / (p2.Y - p1.Y);
                        double intersectX = p1.X + slope * (y - p1.Y);
                        if(intersectX > x){
                            intersections++;
                        }
                    }
                }
                if(intersections % 2 == 1){
                    grid[y][x] = true; // Fill the point if inside the shape
                }
            }
        }
    }

    return grid;

}

bool check_squeare(vector<vector<bool>> &grid, Point &p1, Point &p2){
    int minX = min(p1.X, p2.X);
    int maxX = max(p1.X, p2.X);
    int minY = min(p1.Y, p2.Y);
    int maxY = max(p1.Y, p2.Y);

    /*
    cout << "Original grid: " << endl;
    for(int y = 0; y <= grid.size()-1; ++y){
        for(int x = 0; x <= grid[0].size()-1; ++x){
            cout << grid[y][x];
        }
        cout << endl;                   
    }
        */

    vector<vector<bool>> grid4square(grid.size(), vector<bool>(grid[0].size(), false));
    

    for(int y = minY; y <= maxY; ++y){
        for(int x = minX; x <= maxX; ++x){
            grid4square[y][x] = true;
        }
    }

    /*
    cout << "Square grid: " << endl;
    for(int y = 0; y <= grid4square.size()-1; ++y){
        for(int x = 0; x <= grid4square[0].size()-1; ++x){
            cout << grid4square[y][x];
        }
        cout << endl;                   
    }
        */

    for(int y = minY; y <= maxY; ++y){
        for(int x = minX; x <= maxX; ++x){
            if(grid4square[y][x] && !grid[y][x]){
                return false;
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


    vector<vector<bool>> grid = grid_builder(points);

    vector<SquareSize> uniqueDistancesGood;
    for(int i = 0; i < uniqueDistances.size(); ++i){
        SquareSize s = *next(uniqueDistances.begin(), i);
        cout << "Checking square with distance: " << s.dist << " and points: (" << s.p1.X << "," << s.p1.Y << ") and (" << s.p2.X << "," << s.p2.Y << ")" << endl;
        if(check_squeare(grid, s.p1, s.p2)){
            uniqueDistancesGood.push_back(s);
        }
    }

    return uniqueDistancesGood.back().dist;
    
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
