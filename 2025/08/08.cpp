#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double distance(double a1, double a2, double b1, double b2, double c1, double c2){
    return sqrt(pow((a1-a2),2.0) + pow((b1-b2),2.0) + pow((c1-c2),2.0));
}

struct Point{
    int X, Y, Z;
};

int easy(vector<string> &rows){
    
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
        p.Z = numbers[2];
        points.push_back(p);
        numbers.clear();
    }

    vector<vector<double>> dists;
    for(int i = 0; i < points.size()-1; ++i){
        vector<double> pointdist;
        for(int j = i+1; j < points.size(); ++j){
            pointdist.push_back(distance(points[i].X,points[j].X,
                                         points[i].Y,points[j].Y,
                                         points[i].Z,points[j].Z));
        }
        dists.push_back(pointdist);
    }

    vector<vector<Point>> circuits;

    for(int q = 0; q<1000; ++q){
        //find
        double min = 999999;
        int mini, minj;
        for(int i = 0; i < dists.size(); ++i){
            for(int j = 0; j < dists[i].size(); ++j){
                if(dists[i][j] < min){
                    min = dists[i][j];
                    mini = i;
                    minj = j;
                    //dists[i][j] = 9999999;
                }
            }
        }
        dists[mini][minj] = 9999999;

        Point p1 = points[mini];
        Point p2 = points[mini + minj + 1];

        
        int foundp1 = -1;
        int foundp2 = -1;
        for(int i=0; i<circuits.size(); ++i){
            for(int j = 0; j < circuits[i].size(); ++j){
                if(p1.X == circuits[i][j].X &&
                p1.Y == circuits[i][j].Y &&
                p1.Z == circuits[i][j].Z ){
                    foundp1 = i;
                } 
                if(p2.X == circuits[i][j].X &&
                p2.Y == circuits[i][j].Y &&
                p2.Z == circuits[i][j].Z ){
                    foundp2 = i;
                } 
            }
        }

        if(foundp1 != -1 && foundp2 != -1 && foundp1 != foundp2){
            for(int a = 0; a<circuits[foundp2].size(); ++a){
                circuits[foundp1].push_back(circuits[foundp2][a]);
                
            }
            circuits.erase(circuits.begin() + foundp2);
            //circuits[foundp1].push_back(p1);
            //circuits[foundp1].push_back(p2);
            int foundp1 = -1;
            int foundp2 = -1;
        } else
        if(foundp1 == -1 && foundp2 == -1){
            vector<Point> circuit;
            circuit.push_back(p1);
            circuit.push_back(p2);
            circuits.push_back(circuit);
        } else
        if(foundp1 == -1 && foundp2 != -1){
            circuits[foundp2].push_back(p1);
            int foundp2 = -1;
        } else
        if(foundp1 != -1 && foundp2 == -1){
            circuits[foundp1].push_back(p2);
            int foundp1 = -1;
        }
        

    }

    int result = 1;

    
    for(int a=0; a<3; ++a){
        int maxsize = 0;
        int maxplace = -1;
        for(int i=0; i<circuits.size(); i++){
            if(circuits[i].size()>maxsize){
                maxsize = circuits[i].size();
                maxplace = i;
            }
        }
        result *= maxsize;
        circuits.erase(circuits.begin() + maxplace);
    }

    return 0;
}

int main()
{
    ifstream input;
    vector<string> rows;
    string text;
    input.open("08_mini.txt");
    int answer = 0;
    while (getline(input, text))
    {
        rows.push_back(text);
    }
    answer = easy(rows);
    cout << answer << endl;
    input.close();
    return 0;
}
