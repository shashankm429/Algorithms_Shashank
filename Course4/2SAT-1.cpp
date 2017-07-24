#include <bits/stdc++.h>
using namespace std;
struct node {
	long first;
	long second;
	bool active;
	node(long First, long Second, bool Active) {
		first = First;
		second = Second;
		active = Active;
	}
};
struct Findnode {
	long itemValue;
	vector<long> vnode;
	Findnode(long ItemValue) {
		itemValue = ItemValue;
	}
};
void ReadFile(string filename,vector<node>& inode, long& numberVariable) {
	string a;
	string b;
	string c;
    ifstream inputFile(filename);
	stringstream buffer;
	long int vertexCount = 0;
	try {
		buffer << inputFile.rdbuf();
		buffer >> a;
		numberVariable = stol(a);
		while(buffer >> b >> c) {
			long X = stol(b);
			long Y = stol(c);
			bool active = true;
			node newnode = node(X,Y,active);
			inode.emplace_back(newnode);
		}
	}catch(exception ex) {
		std::cout << ex.what() << endl;
	}
}
void fun1(long item, long vectorIndex, map<long, vector<Findnode> >& v) {
	long absItem = abs(item);
	auto itMapFind = v.find(absItem);
	if (itMapFind == v.end()) {
		vector<Findnode> vNewElement;
		Findnode newFC = Findnode(item);
		newFC.vnode.emplace_back(vectorIndex);
		vNewElement.emplace_back(newFC);
		v.emplace(absItem,vNewElement);
	}
	else {
		bool hasElement = false;
		long vElementIndex = 0;
		vector<Findnode>& vElement = itMapFind->second;
		for (auto iVElement = vElement.begin(); iVElement != vElement.end(); iVElement++) {
			if (iVElement->itemValue  == item) {
			hasElement = true;
				vElement[vElementIndex].vnode.emplace_back(vectorIndex);
			}
			vElementIndex++;
		}
		if (!hasElement) {
			Findnode newFC = Findnode(item);

			newFC.vnode.emplace_back(vectorIndex);

			vElement.emplace_back(newFC);
		}
	}
}
void fun2(vector<node>& inode, map<long,vector<Findnode> >& v) {
	long vectorIndex = 0;
	for (auto it = inode.begin(); it != inode.end(); it++) {
		if (it->active) {
			fun1(it->first, vectorIndex, v);
			fun1(it->second,vectorIndex, v);
		}
		vectorIndex++;
	}
}
void fun3(vector<node>& inode, vector<node>& onode) {

	onode.clear();
	for (auto itC = inode.begin(); itC != inode.end(); itC++) {
		if (itC->active) {
			node newnode = node(itC->first,itC->second, itC->active);
			onode.emplace_back(newnode);
		}
	}
}
void fun4(vector<node>& inode, map<long,vector<Findnode> >& v, vector<node> &onode) {

	long atLoop = 0;
	while (true) {
		bool isMoreReduce = false;

		v.clear();

		atLoop++;


		fun2(inode,v);

		for (auto mItem = v.begin(); mItem != v.end(); mItem++) {
			if (mItem->second.size() == 1) { // only have one size value
				isMoreReduce = true;

				long itemValue = mItem->second.begin()->itemValue;
				vector<long>& itemAtnode = mItem->second.begin()->vnode;

				for (auto itAtnode = itemAtnode.begin(); itAtnode != itemAtnode.end(); itAtnode++)
					inode[*itAtnode].active = false;

			}
		}

		fun3(inode,onode);
		fun3(onode,inode);

		if (inode.size() == 0) isMoreReduce = false;

		if (!isMoreReduce)
			break;
	}



}
int check2SAT(vector<node>& onode,map<long,bool>& variableValue) {
	int retValue = -1;
	int atnodeIndex = 0;

	vector<int> vUnsatisfy;

	for (auto itC = onode.begin(); itC != onode.end(); itC++) {
		auto itF = variableValue.find(itC->first);
		auto itS = variableValue.find(itC->second);

		if (!(itF->second || itS->second)) {
			vUnsatisfy.emplace_back(atnodeIndex);
		}
		atnodeIndex++;
	}

	if (vUnsatisfy.size() == 0)
		return retValue;

	int retValueIndex = (rand() % vUnsatisfy.size());

	retValue = vUnsatisfy[retValueIndex];

	return retValue;
}


bool RandomBool() {
  return rand() % 2 == 1;
}


void fun5(vector<node>& onode, int atIndex,map<long,bool>& variableValue) {
	bool chooseFirst = RandomBool();

	long valueToFlip = LONG_MAX;
	long nValueToFlip = LONG_MIN;

	if (chooseFirst) {
		valueToFlip = onode[atIndex].first;
		nValueToFlip = 0 - valueToFlip;
	} else {
		valueToFlip = onode[atIndex].second;
		nValueToFlip = 0 - valueToFlip;
	}

	auto itPos = variableValue.find(valueToFlip);
	auto itNPost = variableValue.find(nValueToFlip);

	itPos->second = !(itPos->second);
	itNPost->second = !(itNPost->second);

}

bool fun6(vector<node>& onode,  map<long,vector<Findnode> >& v,map<long,bool>& variableValue) {

	long long nLoop = 2 * v.size() * v.size() + 1;

	for (long i = 1; i <= nLoop; i++) {

		//if (i % 1000 == 0)
			//cout << "Papa innrer at x 1000 : " << i << endl;

		int unSatisnode = check2SAT(onode,variableValue);

		if (unSatisnode == -1)
			return true;

		fun5(onode,unSatisnode,variableValue);
	}

	return false;

}

bool result(vector<node>& onode,  map<long,vector<Findnode> >& v) {

	bool satis = false;
	map<long,bool> variableValue;
	int nLoop = log(v.size()) / log(2);
	for (int i = 0; i < nLoop;i++) {
		variableValue.clear();
		for (auto mItem = v.begin(); mItem != v.end(); mItem++) {
			long varIndex = mItem->first;
			bool varValue = RandomBool();

			long nVarIndex = 0 - varIndex;
			bool nVarValue = !varValue;

			variableValue.emplace(varIndex,varValue);
			variableValue.emplace(nVarIndex,nVarValue);
		}
		satis = fun6(onode,v,variableValue);
		if (satis) return true;
	}

	return satis;
}
int main()
 {
	long numberVariable;
	vector<node> inode;
	map<long,vector<Findnode> > v;
	vector<node> onode;
	ReadFile("/Users/shashankmishra/Desktop/2sat1.txt",inode,numberVariable);
	fun4(inode,v,onode);
	bool satis = result(onode,v);
	cout << satis << endl;
	return 0;
}
