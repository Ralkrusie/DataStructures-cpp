#include <stdio.h> 
#include <climits>

#define MAXV 10

//Matrix为邻接矩阵，n为顶点数
//start为起始点 
//Tree代表正在生成的树 
int Prim(int Matrix[MAXV][MAXV], int n, int start){
	int lowCost[MAXV];//存每个点距离Tree最近的边权 

    int closeTree[MAXV];//存每个点距离Tree最近的点

	int sum = 0;//保存最小生成树边权和 
	for (int i = 0; i < n; i++) {//初始化lowCost数组

        closeTree[i] = start;//初始时每个点距离Tree最近的点都是start

		if (i == start) lowCost[i] = 0;//=0代表在Tree中 
		else lowCost[i] = Matrix[i][start];//=Matrix[start][i]也行
	}
	for (int i = 1; i < n; i++) {//找出其余n-1个点 
		//每次都找距离Tree最近的点 
		int minDistance = INT_MAX;//存最小值 
		int minIndex = -1;//最小值对应哪个点 
		for(int j = 0; j < n; j++){
			if (lowCost[j] != 0 && lowCost[j] < minDistance) {
				minDistance = lowCost[j];
				minIndex = j; 
			}
		}
		if (minDistance == INT_MAX) return -1;//图不连通 
		lowCost[minIndex] = 0;//将顶点minIndex加入到Tree中
		sum += minDistance;//累加边权
		//因为Tree多了个点，需要更新其它点到Tree的最小边权 
		for (int j = 0; j < n; j++) {
			if (lowCost[j] != 0 && Matrix[j][minIndex] < lowCost[j]) {
				lowCost[j] = Matrix[j][minIndex];
                
                closeTree[j] = minIndex;//更新距离Tree最近的点
			}			
		}
	}
	return sum;//返回最小生成树边权和 
}

int main(){
	
	//初始化邻接矩阵和顶点数 
	int Matrix[MAXV][MAXV] = {
	{INT_MAX,14,1,6,INT_MAX,INT_MAX},
	{14,INT_MAX,5,INT_MAX,2,INT_MAX},
	{1,5,INT_MAX,9,10,3},
	{6,INT_MAX,9,INT_MAX,INT_MAX,12},
	{INT_MAX,2,10,INT_MAX,INT_MAX,8},
	{INT_MAX,INT_MAX,3,12,8,INT_MAX}
	};
	int n = 6; 
	
	//使用Prim算法求最小生成树的边权和，从顶点0开始(也可从其它点开始)
	int result = Prim(Matrix,n,0);
	
	//输出结果 
	if (result == -1) {
		printf("图不连通");
	} else {
		printf("%d",result); 
	} 
	
	return 0;
} 