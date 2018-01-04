## Agenda

* [Reference](#Reference)  
* [My Solution](#My_Solution)  
    * [problem1](#problem1)  
    * [problem2](#problem2)  
    * [problem3](#problem3)  
    * [problem4](#problem4)  
    * [problem5](#problem5)  
    * [problem6](#problem6)  
    * [problem7](#problem7) 

## Reference

Problems: http://web.stanford.edu/class/cs106b//sections/section03.pdf  
Solutions: http://web.stanford.edu/class/cs106b//sections/section03-solutions.pdf  

## My_Solution

### problem1

<p align="center">
    <img src="assets/s3_1.png" width="600">
    </img>
</p>

Answer: O(n), O(n^2), O(n)  
**Note: the correct solution for the last one is O(1).  
The lesson is: If there is no computation in loop, the loop should be treated as O(1).**

### problem2

<p align="center">
    <img src="assets/s3_2.png" width="600">
    </img>
</p>

Answer:
```c++
void diceRecur(int & n, vector<string> & v ){
    if(n>1){
        n--;
        diceRecur(n, v);
        vector<string> tmp_v = v;
        v.clear();
        for(string x: tmp_v){
            for (int i=1; i<=6; i++){
                v.push_back(to_string(i)+x);
            }
        }
    }else if ( n==1 ){
        for (int i=1; i<=6; i++){
            v.push_back(to_string(i));
        }
    }
}

void diceRolls(int n){
    if (n >= 1){
        vector<string> v;
        diceRecur(n, v);
        for (string x: v){
            cout << x << endl;
        }
    }
}
```
Better solution, which cost much less memory:  
<p align="center">
    <img src="assets/s3_2_solution.png" width="600">
    </img>
</p>

### problem3

<p align="center">
    <img src="assets/s3_3.png" width="600">
    </img>
</p>

Answer:
```c++
void diceSumHelper(int n, vector<int> & v, int & sum ){
    if(n>0 && sum >0){
        for(int i=1; i<=6; i++){
            sum = sum - i;
            if (sum>=0){
                v.push_back(i);
                diceSumHelper(n-1, v, sum);
                v.pop_back();
            }
            sum = sum + i;
        }
    }else if (n == 0 && sum == 0 ){
        cout << "{";
        for (int x: v){
            cout << to_string(x) << ",";
        }
        cout <<"}" << endl;
    }
}

void diceSum(int n, int sum){
    if (n >= 1 and sum >= 1){
        vector<int> v;
        diceSumHelper(n, v, sum);
    }
}
```


### problem4

<p align="center">
    <img src="assets/s3_4.png" width="600">
    </img>
</p>

Answer:
```c++
int largestSum(vector<int> & V, int N){
    if (N <= 0 || V.empty()){
        return 0 ;
    }else{
        int last = V.back();
        V.pop_back();
        int max_sum = largestSum(V, N);
        if (last <= N){
            int max_with_last = last + largestSum(V, N-last);
            max_sum = max(max_sum , max_with_last);
        }
        V.push_back(last);
        return max_sum;
    }
}
```
The recursion loop each element in the vector, and every time remove the element.  
For each element, there is two choice: largest number with or without the element.  

### problem5

<p align="center">
    <img src="assets/s3_5.png" width="600">
    </img>
</p>

Answer:
```c++
int longestCommonSebsequence(string s1, string s2){
    if(s1.size()>0 && s2.size()>0){
        char s1_head = s1[0];
        string s1_rest = s1.substr(1,s1.size());
        //without s1_head
        int longest_length= longestCommonSebsequence(s1_rest, s2);
        //with s1_head, explore if can find s1_head in s2
        if(s2.find_first_of(s1_head) != string::npos){
            string s2_rest = s2.substr(s2.find_first_of(s1_head)+1, s2.size());
            int longest_length_with = 1 + longestCommonSebsequence(s1_rest , s2_rest);
            longest_length = max(longest_length, longest_length_with);
        }
        return longest_length;
    }else{
        return 0;
    }
}
```
similiar solution with previous problem.


### problem6

<p align="center">
    <img src="assets/s3_6.png" width="600">
    </img>
</p>

Answer:
```c++
void printVector(vector<int> V){
    cout << "{" ;
    for(int i=0; i < V.size(); i++){
        if (i == 0){
            cout << to_string(V[i]) ;
        }else{
            cout << ", " << to_string(V[i]) ;
        }
    }
    cout << "}" << endl;
}

void makeChangeHelper(vector<int> V, int N, vector<int> record){
    if (!V.empty()){
        int last = V.back();
        V.pop_back();
        for (int i=0 ; i <= (N / last); i++){
            vector<int> new_record = record;
            new_record.insert(new_record.begin(), i);
            makeChangeHelper(V, N - last*i, new_record);
        }
    }else if(N == 0){
        printVector(record);
    }
}

void makeChange(vector<int> V, const int N){
    vector<int> record;
    makeChangeHelper(V, N, record);
}
```

### problem7

<p align="center">
    <img src="assets/s3_7.png" width="600">
    </img>
</p>

Answer:
```c++
bool canBalance(vector<int> V, int N){
    if ( !V.empty() ){
        int last = V.back();
        V.pop_back();
        if (canBalance(V, N + last) || canBalance(V, N - last)){
            return true;
        }
    }else if (N == 0) {
        return true;
    }
    return false;
}
```
