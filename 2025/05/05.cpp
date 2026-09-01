#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void check_intervals(vector<pair<long,long>> &intervals){

    for(size_t i = 0; i < intervals.size()-1; ++i){
        pair<long,long> &interval = intervals[i];
        for(size_t j = i+1; j < intervals.size(); ++j){
            pair<long,long> &new_interval = intervals[j];

            if(new_interval.second < interval.first || interval.second < new_interval.first){
                continue;
            }
            if(new_interval.first < interval.first && interval.first <= new_interval.second){
                interval.first = new_interval.first;
                intervals.erase(intervals.begin() + j);
                j--;
                break;
            }
            if(new_interval.second > interval.second && new_interval.first <= interval.second){
                interval.second = new_interval.second;
                intervals.erase(intervals.begin() + j);
                j--;
                break;
            }

            if(new_interval.first <= interval.first && new_interval.second >= interval.second){
                interval.first = new_interval.first;
                interval.second = new_interval.second;
                intervals.erase(intervals.begin() + j);
                j--;
                break;
            }
            if(new_interval.first >= interval.first && new_interval.second <= interval.second){
                intervals.erase(intervals.begin() + j);
                j--;
                break;
            }

        }

    }

}

long hard(vector<string> &data){

    vector<pair<long,long>> intervals;
    unsigned long result = 0;

    for(size_t i = 0; i < 194; ++i){

        pair<long, long> new_interval;
        auto pos = data[i].find("-");
        new_interval.first  = stol(data[i].substr(0,pos));
        new_interval.second = stol(data[i].substr(pos+1,data[i].size()-pos+1));
        
        if(new_interval.first > new_interval.second) return 0;

        bool can_push = true;
        for(size_t j = 0; j < intervals.size(); ++j){
            pair<long,long> &interval = intervals[j];
            if(new_interval.second < interval.first || interval.second < new_interval.first){
                continue;
            }
            if(new_interval.first < interval.first && interval.first <= new_interval.second){
                interval.first = new_interval.first;
                can_push = false;
            }
            if(new_interval.second > interval.second && new_interval.first <= interval.second){
                interval.second = new_interval.second;
                can_push = false;
            } 
            if(new_interval.first <= interval.first && new_interval.second >= interval.second){
                interval.first = new_interval.first;
                interval.second = new_interval.second;
                can_push = false;
            }
            if(new_interval.first >= interval.first && new_interval.second <= interval.second){
                can_push = false;
            }
        }
        if(can_push) intervals.push_back(new_interval);

        check_intervals(intervals);

    }
    
    vector<long> interval_size;
    for(pair<long,long> interval : intervals){
        result += (interval.second - interval.first + 1);
        interval_size.push_back(interval.second - interval.first + 1);
    }

    return result;
}

int easy(vector<string> &data){

    vector<pair<long,long>> intervals;
    vector<long> numbers;
    int result = 0;

    for(size_t i = 0; i < 194; ++i){

        pair<long, long> interval;
        auto pos = data[i].find("-");
        interval.first  = stol(data[i].substr(0,pos));
        interval.second = stol(data[i].substr(pos+1,data[i].size()-pos+1));
        intervals.push_back(interval);

    }

    for(size_t i = 195; i < data.size(); ++i){
        
        numbers.push_back(stol(data[i]));

    }

    for(long number : numbers){

        for(pair<long,long> interval : intervals){

            if(number >= interval.first && number <= interval.second){
                result++;
                break;
            }

        }

    }

    return result;
}

int main()
{
    ifstream input;
    vector<string> rows;
    string text;
    input.open("05.txt");
    int answer = 0;
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
