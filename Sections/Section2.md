## Reference:
[Problem set](https://codestepbystep.com/problemset/view?id=4)

[Solution](http://web.stanford.edu/class/cs106b//sections/section02-solutions.pdf)

## Note:
* map sort iterator by key
* set sort element asc by default

## My work:
[problem1](https://codestepbystep.com/problem/view/cpp/collections/map/biggestFamily)
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