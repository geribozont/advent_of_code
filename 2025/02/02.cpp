#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

long long check_part2(long long value) {
    string s = to_string(value);
    int n = s.size();
    
    for (int len = 1; len <= n / 2; ++len) {
        if (n % len == 0) { // Potential period length
            string unit = s.substr(0, len);
            bool match = true;
            for (int j = len; j < n; j += len) {
                if (s.substr(j, len) != unit) {
                    match = false;
                    break;
                }
            }
            if (match) return value;
        }
    }
    return 0;
}

long long check_easy(long long value) {
    string s = to_string(value);
    int n = s.size();
    if (n % 2 == 0 && s.substr(0, n / 2) == s.substr(n / 2)) {
        return value;
    }
    return 0;
}

long long solve(const string& input_line, bool rigorous_check = true) {

    long long total_sum = 0;
    stringstream ss(input_line);
    string range_str;

    while (getline(ss, range_str, ',')) {
        size_t dash_pos = range_str.find('-');
        if (dash_pos == string::npos) continue;

        long long start = stoll(range_str.substr(0, dash_pos));
        long long end = stoll(range_str.substr(dash_pos + 1));

        for (long long i = start; i <= end; ++i) {
            total_sum += (rigorous_check ? check_part2(i) : check_easy(i));
        }
    }
    return total_sum;
}

int main() {
    ifstream file("02.txt");
    if (!file.is_open()) {
        cerr << "Error: File 02.txt not found!" << endl;
        return 1;
    }

    string line;
    if (getline(file, line)) {
        cout << "Answer Part 2: " << solve(line, false) << endl;
    }

    return 0;
}
