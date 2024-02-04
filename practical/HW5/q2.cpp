#include <iostream>

using namespace std;


bool srch(string input, int pointer, string data[], int line, int length, int index1, int index2) {
    if (input[pointer] != data[index1][index2]) return false;
    if (pointer == input.length() - 1) return true;
    bool res = false;
    char temp = data[index1][index2];
    data[index1][index2] = ' ';
    if (0 < index1) res |= srch(input, pointer + 1, data, line, length, index1 - 1, index2);
    if (0 < index2) res |= srch(input, pointer + 1, data, line, length, index1, index2 - 1);
    if (line-1  > index1) res |= srch(input, pointer + 1, data, line, length, index1 + 1, index2);
    if (length-1  > index2) res |= srch(input, pointer + 1, data, line, length, index1, index2 + 1);
    data[index1][index2] = temp;
    return res;
}

int main() {
    int line, length, count;
    cin >> line >> length;
    string data[line];
    for (int i = 0; i < line; ++i) {
        cin >> data[i];
    }
    cin >> count;
    string input;
    bool flag;
    for (int i = 0; i < count; ++i) {
        flag = true;
        cin >> input;
        for (int j = 0; j < line && flag; ++j) {
            for (int k = 0; k < length && flag; ++k) {
                if (srch(input, 0, data, line, length, j, k)) {
                    flag = false;
                    cout << input << endl;
                }
            }
        }
    }

    return 0;
}

