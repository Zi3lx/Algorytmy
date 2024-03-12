#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int lcsLength(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();

    // Create two rows for storing the lengths of LCS
    vector<int> prevRow(n + 1, 0);
    vector<int> currRow(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                currRow[j] = prevRow[j - 1] + 1;
            }
            else {
                currRow[j] = max(prevRow[j], currRow[j - 1]);
            }
        }
        // Move current row to previous row
        prevRow = currRow;
    }
    return prevRow[n];
}

string lcs(const string& X, const string& Y, int m, int n)
{
    vector<vector<int>> LCS_table(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            else
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
        }
    }

    int index = LCS_table[m][n];
    char* lcsAlgo = new char[index + 1];
    lcsAlgo[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcsAlgo[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }

        else if (LCS_table[i - 1][j] > LCS_table[i][j - 1])
            i--;
        else
            j--;
    }

    return string(lcsAlgo);
}

string generateRandomString(int n, int k) {
    string result;
    for (int i = 0; i < n; i++) {
        char randomChar = 'A' + rand() % k;
        result.push_back(randomChar);
    }
    return result;
}

int main() {
    string X = "aabba";
    string Y = "bbab";
    int m = X.length(), n = Y.length();

    int length = lcsLength(X, Y);
    string lcsSub = lcs(X, Y, m, n);
    cout << "Length of Longest Common Subsequence: " << length << " " << lcsSub << endl;

    srand(time(0));

    vector<int> ks = { 2, 4, 8, 16 };
    vector<int> ns = { 100, 500, 1000 };

    for (int k : ks) {
        for (int n : ns) {
            string X = generateRandomString(n, k);
            string Y = generateRandomString(n, k);

            int length = lcsLength(X, Y);

            // Calculate the ratio of LCS length to the length of the input strings
            double ratio = static_cast<double>(length) / n;

            // Print the results
            cout << "k = " << k << ", n = " << n << ": ";
            cout << "Length of LCS: " << length << ", Ratio: " << ratio << endl;
        }
    }

    return 0;

    return 0;
}
