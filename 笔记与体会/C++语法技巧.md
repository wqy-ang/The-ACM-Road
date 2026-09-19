# 学习过程中遇到的C++技巧
> 暂时是想到什么就添加什么

## 重载运算符
```cpp
struct node{
    int chinese, math, english, sum;
};

// 这不是一个单纯的函数
// operator< 是C++ 自定义类型的 “隐式比较规则”
bool operator<(node a, node b){
    // TODO: 实现比较逻辑，按照总分、语文、数学、英语的优先级排序
    if(a.sum == b.sum) {
        if(a.chinese == b.chinese) {
            if(a.math == b.math){
                return a.english < b.english;
            }
            else return a.math < b.math;
        }
        else return a.chinese < b.chinese;
    }
    else return a.sum < b.sum;
} // 你重载的 bool operator<(node a, node b)
  // 是给 priority_queue 提供了「如何判断一个
  // node 是否 “小于” 另一个 node」的规则
```