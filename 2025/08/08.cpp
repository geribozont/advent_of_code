#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <set>

using namespace std;

double distance(double a1, double a2, double b1, double b2, double c1, double c2){
    return sqrt(pow((a1-a2),2.0) + pow((b1-b2),2.0) + pow((c1-c2),2.0));
}

struct Point{
    int X, Y, Z;

};

struct Distance{
    double dist;
    Point p1, p2;
    bool operator < (const Distance& d) const{
        return dist < d.dist;
    }
};


long long easy(vector<string> &rows){
    
    // pontok beolvasása
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

    set<Distance> uniqueDistances;
    for(int i = 0; i < points.size()-1; ++i){
        for(int j = i+1; j < points.size(); ++j){
            Distance d;
            d.dist = distance(points[i].X,points[j].X,
                              points[i].Y,points[j].Y,
                              points[i].Z,points[j].Z);
            d.p1 = points[i];
            d.p2 = points[j];
            uniqueDistances.insert(d);
        }
    }

    vector<Point> unchecked_points;
    for(int i = 0; i < points.size(); ++i){
        unchecked_points.push_back(points[i]);
    }
    vector<Point> unique_circuit;
    vector<vector<Point>> circuits;
    int connections = 0;
    int counter = 0;

    int last_p1_X, last_p2_X;
    
    while(unchecked_points.size() > 0 || circuits.size() != 1 /*&& counter < 10*/){


        Distance d = *uniqueDistances.begin();
        last_p1_X = d.p1.X;
        last_p2_X = d.p2.X;

        /*
        cout << "Smallest distance: " << d.dist << " between points (" 
             << d.p1.X << "," << d.p1.Y << "," << d.p1.Z << ") and ("
             << d.p2.X << "," << d.p2.Y << "," << d.p2.Z << ")" << endl;
        */

        bool foundp1 = false;
        bool foundp2 = false;
        int foundp1_circuit = -1;
        int foundp2_circuit = -1;
        for(int i = 0; i < circuits.size(); ++i){
            
            for(int j = 0; j < circuits[i].size(); ++j){
                if(circuits[i][j].X == d.p1.X && circuits[i][j].Y == d.p1.Y && circuits[i][j].Z == d.p1.Z){
                    foundp1 = true;
                    foundp1_circuit = i;
                }
                if(circuits[i][j].X == d.p2.X && circuits[i][j].Y == d.p2.Y && circuits[i][j].Z == d.p2.Z){
                    foundp2 = true;
                    foundp2_circuit = i;
                }
            }
            
        }
        if(foundp1 && !foundp2){
            circuits[foundp1_circuit].push_back(d.p2);
            connections++;
        } else if(!foundp1 && foundp2){
            circuits[foundp2_circuit].push_back(d.p1);
            connections++;
        } 
        else if(foundp1 && foundp2 && foundp1_circuit != foundp2_circuit){
            circuits[foundp1_circuit].insert(circuits[foundp1_circuit].end(), circuits[foundp2_circuit].begin(), circuits[foundp2_circuit].end());
            circuits.erase(circuits.begin() + foundp2_circuit);
            connections++;
        }
        else if(!foundp1 && !foundp2){
            vector<Point> new_circuit;
            new_circuit.push_back(d.p1);
            new_circuit.push_back(d.p2);
            circuits.push_back(new_circuit);
            connections++;
        }

        for(int i = 0; i < unchecked_points.size(); ++i){
            if((unchecked_points[i].X == d.p1.X && unchecked_points[i].Y == d.p1.Y && unchecked_points[i].Z == d.p1.Z) ||
               (unchecked_points[i].X == d.p2.X && unchecked_points[i].Y == d.p2.Y && unchecked_points[i].Z == d.p2.Z)){
                unchecked_points.erase(unchecked_points.begin() + i);
                --i;
            }
        }

        /*
        for(int i = 0; i < circuits.size(); ++i){
            cout << "Circuit " << i << ": ";
            for(int j = 0; j < circuits[i].size(); ++j){
                cout << "(" << circuits[i][j].X << "," << circuits[i][j].Y << "," << circuits[i][j].Z << ") ";
            }
            cout << endl;
        
        }
        cout << "Connections made: " << connections << endl;
        cout << "Unchecked points remaining: " << unchecked_points.size() << endl;
        cout << endl;

        counter++;
        */


        uniqueDistances.erase(uniqueDistances.begin());

    }

    /*
    // For easy
    int result = 1;
    for(int i = 0; i < 3; ++i){
       
        int maxsize = 0;
        int maxplace = -1;
        for(int j = 0; j < circuits.size(); ++j){
            if(circuits[j].size() > maxsize){
                maxsize = circuits[j].size();
                maxplace = j;
            }
        }
        cout << "Circuit " << maxplace << " has size " << maxsize << endl;
        if(maxplace != -1){
            result *= maxsize;
        }
        circuits.erase(circuits.begin() + maxplace);

    }
        */

        for(int i = 0; i < circuits.size(); ++i){
            cout << "Circuit " << i << ": ";
            for(int j = 0; j < circuits[i].size(); ++j){
                cout << "(" << circuits[i][j].X << "," << circuits[i][j].Y << "," << circuits[i][j].Z << ") ";
            }
            cout << endl;
        
        }
        cout << "Connections made: " << connections << endl;
        cout << "Unchecked points remaining: " << unchecked_points.size() << endl;
        cout << endl;

        cout << "Unchecked distances remaining: " << uniqueDistances.size() << endl;
        long long result = (long long)last_p1_X * last_p2_X;
        cout << "Last points: (" << last_p1_X << "," << last_p2_X << ")" << endl;
        return result;
}

int main()
{
    ifstream input;
    vector<string> rows;
    string text;
    input.open("08.txt");
    long long answer = 0;
    while (getline(input, text))
    {
        rows.push_back(text);
    }
    answer = easy(rows);
    cout << "Answer: " << answer << endl;
    input.close();
    return 0;
}
