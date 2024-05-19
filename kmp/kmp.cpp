#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


string readStringFromFile(string fileName) {
    string text = "";
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            text += line;
        }
        file.close();
    }
    return text;
}
vector<int> naiveSearch(const string& text, const string& pattern) {
    vector<int> positions;
    int n = text.size();
    int m = pattern.size();

    for (int i = 0; i <= n - m; ++i) {
        int j;
        for (j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m) {
            positions.push_back(i);
        }
    }
    return positions;
}

vector<int> rabinKarpSearch(const string& text, const string& pattern) {
    int prime = 101;
    vector<int> positions;
    int n = text.size();
    int m = pattern.size();
    int pHash = 0, tHash = 0, h = 1;

    for (int i = 0; i < m - 1; ++i)
        h = (h * 256) % prime;

    for (int i = 0; i < m; ++i) {
        pHash = (256 * pHash + pattern[i]) % prime;
        tHash = (256 * tHash + text[i]) % prime;
    }

    for (int i = 0; i <= n - m; ++i) {
        if (pHash == tHash) {
            int j;
            for (j = 0; j < m; ++j) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m) {
                positions.push_back(i);
            }
        }
        if (i < n - m) {
            tHash = (256 * (tHash - text[i] * h) + text[i + m]) % prime;
            if (tHash < 0)
                tHash = (tHash + prime);
        }
    }
    return positions;
}

vector<int> computeLPSArray(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int length = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> positions;
    int n = text.size();
    int m = pattern.size();
    vector<int> lps = computeLPSArray(pattern);
    int i = 0, j = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            positions.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return positions;
}

int main() {
    string text1 = readStringFromFile("text1.txt");
    string pattern1 = readStringFromFile("pattern1.txt");
    string text = "ABABCABABABABCABAB";
    string pattern = "ABABCABAB";

    cout << "Testing on small example:\n";
    cout << "Naive Search: ";
    vector<int> result = naiveSearch(text1, pattern1);
    for (int pos : result) cout << pos << " ";
    cout << "\n";

    result = rabinKarpSearch(text1, pattern1);
    cout << "Rabin-Karp Search: ";
    for (int pos : result) cout << pos << " ";
    cout << "\n";

    result = kmpSearch(text1, pattern1);
    cout << "KMP Search: ";
    for (int pos : result) cout << pos << " ";
    cout << "\n";

    // Przygotowanie dużych danych testowych
    string largeText(1000000, 'A');
    largeText += "B";
    string largePattern = "AAAAB";

    cout << "\nTesting on large example:\n";

    return 0;
}