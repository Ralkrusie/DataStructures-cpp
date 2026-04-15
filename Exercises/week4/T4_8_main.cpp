/*日志分析*/
#include <stack>
#include <iostream>
#include <string>

int main(){
    int n;
    std::cin >> n;
    std::stack<int> mainStack;
    std::stack<int> maxStack;
    for (int i = 0; i < n; i++){
        int op;
        std::cin >> op;
        switch (op){
        case 0:
            int weight;
            std::cin >> weight;
            mainStack.push(weight);
            if (maxStack.empty() || maxStack.top() <= weight){
                maxStack.push(weight);
            }
            break;
        case 1:
            if (!mainStack.empty()){
                if (mainStack.top() == maxStack.top()){
                    maxStack.pop();
                }
                mainStack.pop();
            }
            break;
        case 2:
            if (mainStack.empty()){
                std::cout << "0\n";
                break;
            }
            std::cout << maxStack.top() << std::endl;
            break;
        default:
            break;
        }
    }
}