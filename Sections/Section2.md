## Agenda
* [Reference](#Reference)  
* [Note](#Note)  
* [My_work](#My_work)  
    * [problem1](#problem1)  
    * [problem2](#problem2)  
    * [problem3](#problem3)  
    * [problem4](#problem4)  
    * [problem5](#problem5)  
    * [problem6](#problem6)  
    * [problem7](#problem7) 


## Reference
[Problem_set](https://codestepbystep.com/problemset/view?id=4)  
[Solution](http://web.stanford.edu/class/cs106b//sections/section02-solutions.pdf)

## Note
* map sort iterator by key
* set sort element asc by default
* map [operator](http://en.cppreference.com/w/cpp/container/map/operator_at)
    * ***input_map[key]=value***, this statement will insert the key-value pair 
     if the key does not exist, or update the value if the key exists.
    * ***input_map[key]***, this statement will return the value if the key exists,
    will return 0 for int type **if the key does not exists and insert {key, 0} into map**.
    For string type, "" is the default value.
```c++
int main ()
{
    map<string, int> input_map = {{"a",1}};
    cout << input_map["a"] << endl;
    cout << input_map["b"] << endl;
    input_map["c"]=3;
    input_map["c"]=4;
    input_map.emplace("c",5);
    for (auto it: input_map){
        cout<<it.first<<it.second<<endl;
    }
    return 0;
}
```
```text
output:
1
0
a1
b0
c4
```
* cast char to int as: 
```c++
char x = '10';
cout << (int)x - '0' << endl; //implicit casting
#the same as
cout << (int)x - 48 << endl; // integer start from 48 in ascii.
```
* identify if set contain the element:
```c++
if (set.find(x) == set.end()){
    cout << "This set not contain x." << endl;
}
```

## My_work
### problem1
[biggestFamily](https://codestepbystep.com/problem/view/cpp/collections/map/biggestFamily)
```c++
void biggestFamily(const string file_name){
    ifstream ifs;
    ifs.open(file_name);
    string line;
    map<string , set<string> > family_graph ;
    set<string> member_name;
    while(getline(ifs, line)){
        int blank_space_pos = line.find(" ");
        string first_name = line.substr(0, blank_space_pos);
        string family_name = line.substr(blank_space_pos + 1);
        auto result = family_graph.find(family_name);
        if (result!=family_graph.end()){
            //found
            member_name = result -> second;
            member_name.insert(member_name.begin(), first_name);
            family_graph.erase(result);
        }else {
            //not found
            member_name = {};
            member_name.insert(first_name);
        }
        family_graph.emplace(family_name , member_name );
    }
    int max_mem_cnt=0;
    for (auto it : family_graph){
        if (it.second.size() > max_mem_cnt){
            max_mem_cnt = it.second.size()  ;
        }
    }
    for (auto it : family_graph){
        string member = "";
        if (it.second.size() == max_mem_cnt){
            for (string name: it.second){
                member = member + " " + name;
            }
            cout << it.first
                 << " family:"
                 << member
                 << endl;
        }

    }
}
```

### problem2
[rarest](https://codestepbystep.com/problem/view/cpp/collections/map/rarest)
```c++
string rarest(const Map<string, string> & input_map){
    if (input_map.size() > 0 ){
        Vector<string> value_v = input_map.values();
        map<string, int> value_cnt;
        const int length = value_v.size();
        for (int i=0; i < length; i++){
            const string key = value_v[i];
            auto res = value_cnt.find(key);
            if (res != value_cnt.end()){
                //found
                int cnt = res->second + 1;
                value_cnt.erase(res);
                value_cnt.emplace(key, cnt);
            }else{
                //not found
                value_cnt.emplace(key, 1);
            }
        }
        int min_cnt = numeric_limits<int>::max();
        string output;
        for (auto it: value_cnt){
            if (it.second < min_cnt){
                output = it.first;
                min_cnt = it.second;
            }
        }
        return output;
    }else {
        throw string("input invalid");
    }
}
```
### problem3
[evaluateMathExpression](https://codestepbystep.com/problem/view/cpp/recursion/evaluateMathExpression?problemsetid=4)  
```c++
int evaluate(const string & s, int & i ){
    if(i > s.length()){
        return 0;
    }
    char ch = s[i++];
    if (isdigit(ch)){
        return ch - '0';
    }else {
        int left = evaluate(s, i);
        char op = s[i++];
        int right = evaluate(s, i);
        i++;
        if (op == '+'){
            return left + right;
        } else {
            return left * right;
        }
    }
}

int evaluateMathExpression(const string & s){
    int i = 0 ;
    return evaluate(s, i);
}
```

### problem4
[recursionMysteryComma](https://codestepbystep.com/problem/view/cpp/recursion/recursionMysteryComma?problemsetid=4)

### problem5
[stutterStack](https://codestepbystep.com/problem/view/cpp/recursion/stutterStack?problemsetid=4)
```c++
void stutterStack(Stack<int> & input){
    if (!input.isEmpty() ){
        int current_num = input.pop();
        if (!input.isEmpty()){
            stutterStack(input);
        }
        input.push(current_num);
        input.push(current_num);
    }
}
```

### problem6
[isHappyNumber](https://codestepbystep.com/problem/view/cpp/collections/set/isHappyNumber?problemsetid=4)
```c++
bool isHappyNumber(int input){
    set<int> stock ;
    do{
        stock.insert(input);
        string s = to_string(input) ;
        input = 0;
        for (char x: s){
            input += pow((int)x - '0',2);
        }
    }while (input !=1 && stock.find(input) == stock.end());
    
    if (input == 1){
        return true;
    }
    return false;
}
```

### problem7
[reverseLines](https://codestepbystep.com/problem/view/cpp/recursion/reverseLines?problemsetid=4)
```c++
void reverseLines(ifstream & ifs){
    string line;
    if(getline(ifs, line)){
        reverseLines(ifs);
        cout << line << endl;
    }
}
```