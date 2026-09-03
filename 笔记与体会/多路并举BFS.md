# 多路并举的 BFS

## 小技巧
多路并举时用 vector 代替 queue，使用
```cpp
vector q(vector<int>());
while(!q.empty) {
    auto tmp = move(q);
    // ...
}
// 或者
// for(int i=0; !q.empty; i++) {
//     auto tmp = move(q);
// }
```
其中 move(q) 之后 q 为空，这样能记录下第某次的BFS情况，并且可以及时中断某些不合要求的路。