#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
bool flag;
int res;

bool check_chaos(const map<int, int>& freq){
    for(auto it = freq.begin(); it != freq.end(); it++){
        if(it->second > 2){
            return true;
        }
    }
    return false;
}

void merge(int start, int mid, int end, vector<int>& arr){

    map<int, int> freq;
    vector<int> left, right;
    for(int i = start; i <= mid; i++){
        left.push_back(arr[i]);
    }
    for(int i = mid+1; i <= end; i++){
        right.push_back(arr[i]);
    }
    left.push_back(INT_MAX);
    right.push_back(INT_MAX);
    int arr_i = start;
    int left_i = 0;
    int right_i = 0;
    while(arr_i <= end){
        if(left[left_i] < right[right_i]){
            arr[arr_i] = left[left_i];
            arr_i++;
            left_i++;
        } else {
            arr[arr_i] = right[right_i];
            arr_i++;
            right_i++;
            if(left[left_i] != INT_MAX){
                freq[left[left_i]]++;
                res++;
            }
        }
    }
    if(check_chaos(freq)){
        flag = true;
    }
}

void merge_sort(int start, int end, vector<int>& arr){
    if(start != end){
        int mid = (start+end)/2;
        merge_sort(start, mid, arr);
        merge_sort(mid+1, end, arr);
        merge(start, mid, end, arr);
    }
}

// Complete the minimumBribes function below.
void minimumBribes(vector<int> q) {

    merge_sort(0, (int)q.size()-1, q);
    if(flag){
        cout << "Too chaotic\n";
    } else {
        cout << res << "\n";
    }
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
