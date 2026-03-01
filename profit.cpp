#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Project {
    int capital;
    int profit;

    //<
    bool operator<(const Project& o) const {
        return capital < o.capital;
    }

};

int main() {
// 错误开始
    int n;
    int k;
    int w;//资本
    vector<Project> projects(n);
    priority_queue<int> max_heap;

    cin>>k>>w>>n;
// 错误结束
// ACM模式下，当初始化变量之后，应该立马cin输入赋值，所以说 “vector<Project> projects(n);”应该在n赋值后，
// 不然n是一个垃圾值，往往此时n特别大，系统给当前任务分配的内存有限，访问了非法的内存地址，导致段错误segment fault


    for (int i = 0; i < n; i++) {
        cin >> projects[i].capital;
    }

    for (int i = 0; i < n; i++) {
        cin >> projects[i].profit;
    }
    sort(projects.begin(), projects.end());
    int project_idx = 0;

    for (int i = 0; i < k; i++) {
        while (project_idx < n && projects[project_idx].capital <= w ) {
            max_heap.push(projects[project_idx].profit);
            project_idx++;

        } 
        if (max_heap.empty()) {
            break;
        }

        w += max_heap.top();
        max_heap.pop();
        
    }
    cout << w << endl;
    return 0;
}