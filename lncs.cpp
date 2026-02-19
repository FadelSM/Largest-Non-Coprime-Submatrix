#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */

int solve(vector<vector<int>> matrix) {
    int n = matrix.size();
    if (n == 0) return 0;
    int m = matrix[0].size();
    int max_area = 0;

    // Fix the starting row
    for (int r1 = 0; r1 < n; ++r1) {
        // This will store the GCD of columns from row r1 to r2
        vector<int> col_gcds(m, 0);

        // Fix the ending row
        for (int r2 = r1; r2 < n; ++r2) {
            int current_height = r2 - r1 + 1;

            // Update GCD for each column to include the new row r2
            for (int j = 0; j < m; ++j) {
                if (r1 == r2) col_gcds[j] = matrix[r2][j];
                else col_gcds[j] = gcd(col_gcds[j], matrix[r2][j]);
            }

            // Find the longest contiguous sub-segment in col_gcds with GCD > 1
            int left = 0;
            while (left < m) {
                if (col_gcds[left] <= 1) {
                    left++;
                    continue;
                }
                
                // Try to expand from 'left'
                int right = left;
                int running_gcd = col_gcds[left];
                
                while (right < m) {
                    int next_gcd = gcd(running_gcd, col_gcds[right]);
                    if (next_gcd > 1) {
                        running_gcd = next_gcd;
                        int width = right - left + 1;
                        max_area = max(max_area, current_height * width);
                        right++;
                    } else {
                        break;
                    }
                }
                left++; // Move to next starting point
            }
        }
    }
    return max_area;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < m; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    int result = solve(matrix);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
