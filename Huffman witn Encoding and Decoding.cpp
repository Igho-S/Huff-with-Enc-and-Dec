#include <bits/stdc++.h>
#define MAX_TREE_HT 256
using namespace std;
//Хаззан Омотола

struct MinHeapNode{
	char data;
	int freq;
	MinHeapNode *left, *right;

	MinHeapNode(char data, int freq){
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

struct compare{ //сравнить, что имеет более высокий приоритет
	bool operator()(MinHeapNode* l, MinHeapNode* r){
		return (l->freq > r->freq);
	}
};

//Очередь с приоритетом для хранения дерева кучи в соответствии со значением корневого узла кучи.
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

// храненить частоты символов входных данных
map<char, int> freq;

void calcFreq(string str, int n){//функция для сопоставления каждого символа с его частотой во входной строке
	for (int i=0; i<str.size(); i++)
		freq[str[i]]++;
}

map<char, string> codes; //здесь, чтобы сопоставить каждый символ с его значением Хауфмана

void storeCodes(struct MinHeapNode* root, string str){ //функция для хранения символов вместе с их значением Хаффмана в хэш-таблице
	if (root==NULL)
		return;
	if (root->data != '$')
		codes[root->data]=str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}

void HuffmanCodes(int size){ //функция для построения дерева и сохранения его в minHeap
	struct MinHeapNode *left, *right, *top;
	for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++)
		minHeap.push(new MinHeapNode(v->first, v->second));
	while (minHeap.size() != 1){
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		top = new MinHeapNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	storeCodes(minHeap.top(), "");
}

void printCodes(struct MinHeapNode* root, string str){ //распечатать коды и значения Хаффмана
	if (!root)
		return;
	if (root->data != '$')
		cout << root->data << ": " << str << "\n";
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

/*эта функция перебирает закодированную строку s
если s[i]=='1', то переходим к узлу->справа
если s[i]=='0', то переходим к узлу->влево
если конечный узел добавляет node->data к нашей выходной строке*/
string decode_file(struct MinHeapNode* root, string s){
	string ans = "";
	struct MinHeapNode* curr = root;
	for (int i=0;i<s.size();i++){
		if (s[i] == '0')
		curr = curr->left;
		else
		curr = curr->right;

		// левый узел
		if (curr->left==NULL and curr->right==NULL){
			ans += curr->data;
			curr = root;
		}
	}
	return ans+'\0';
}

int main(){
string str = "psychology is a biological science"; //психология это биологическая наука
string encodedString, decodedString;

calcFreq(str, str.length());

HuffmanCodes(str.length());

cout << "Character With their Frequencies:\n"; //символы с их частотами
for (auto v=codes.begin(); v!=codes.end(); v++)
		cout << v->first <<' ' << v->second << endl;

for (auto i: str) encodedString+=codes[i];

cout << "\nEncoded Huffman data:\n" << encodedString << endl; //закодированные данные

decodedString = decode_file(minHeap.top(), encodedString);

cout << "\nDecoded Huffman Data:\n" << decodedString << endl; //декодированные данные

}

