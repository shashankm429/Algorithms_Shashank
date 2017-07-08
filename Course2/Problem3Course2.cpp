# include <iostream>
# include <vector>
# include <fstream>
# include <string>
# include <functional>
# include <queue>
# include <algorithm>
using namespace std;
void store(string);
int mm(void);
const int MOD = 10000;
vector<int> input_stream;
int main(int argc, char** argv) {
	store("/Users/shashankmishra/Desktop/Median.txt");
	int sum = mm();
	cout << sum;
}
void store(string filename) {
	ifstream infile;
	infile.open(filename, ios::in);
	int tmp;
	int c = 0;
	int i = 0;
	while (infile >> tmp)
		input_stream.push_back(tmp);
	infile.close();
}
int mm(void) {
	priority_queue<int, vector<int>, greater<int>> min_heap;
	priority_queue<int> max_heap;
	int c = 0;
	max_heap.push(min(input_stream[0], input_stream[1]));
	c += input_stream[0];
	min_heap.push(max(input_stream[0], input_stream[1]));
	c += max_heap.top();
	for (int i = 2; i < input_stream.size(); ++i) {
		if (input_stream[i] < max_heap.top())
			max_heap.push(input_stream[i]);
		else
			min_heap.push(input_stream[i]);
		if (min_heap.size() > max_heap.size() and min_heap.size() - max_heap.size() > 1) {
			int tmp = min_heap.top();
			min_heap.pop();
			max_heap.push(tmp);
		}
		else if (max_heap.size() > min_heap.size() and max_heap.size() - min_heap.size() > 1) {
			int tmp = max_heap.top();
			max_heap.pop();
			min_heap.push(tmp);
		}
		int val;
		if (i % 2)
			c += + max_heap.top();
		else {
			if (max_heap.size() > min_heap.size())
				c += + max_heap.top();
			else
				c += min_heap.top();
		}
		c = c % MOD;
	}
	return c;
}
