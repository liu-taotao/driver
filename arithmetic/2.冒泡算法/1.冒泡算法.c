/*
功能：使用选择排序法对数组data进行排序
输入参数：
	data[]，已知数据散乱的数组
	n，元素的个数
输出参数：    [0,2,5,6,3,9,1,4,8]
	data[]，排好序的数组
返回值：无 
*/
void BubbleSort(int data[], int n)
{
	int i, j, t;
	for (i = 0; i < n-1; i++) {
		for (j = 0; j < n-i; j++) {
			if (data[j+1] < data[j]) {
				t = data[j+1];
				data[j+1] = data[j];
				data[j] = t;
			}
		}
	}
}
