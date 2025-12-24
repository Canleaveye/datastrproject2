#include <iostream>
#include <fstream>
#include <map>
using namespace std;

// 清洗字符串（仅保留字母且转为小写）
string cleanString(string str) {
    string result;
    for (unsigned char ch : str) {
        if (isalpha(ch))
            result += tolower(ch);
    }
    return result;
}


class WordCounter {
private:
    map<string, int> wordMap;
public:

    void addWord(string word) {         // 对外唯一接口：添加单词并计数
        word = cleanString(word);
        if (!word.empty()) ++wordMap[word];
    }

    int getUniqueWordCount() { return wordMap.size(); }  // 获取不同单词的数量

    void displayResults() {               // 显示所有单词及其计数
        for (auto& pair : wordMap)
            cout << pair.first << " : " << pair.second << '\n';
    }
};

// 从文件加载内容并统计单词
void loadFileAndCount(WordCounter& counter, string filename) {
    ifstream fileStream(filename);
    string word;
    while (fileStream >> word) {
        counter.addWord(word);
    }
}


int main() {
    WordCounter counter;
    loadFileAndCount(counter, "article.txt");  // 确保同目录下有该文件
    cout << "总词种数：" << counter.getUniqueWordCount() << '\n';
    counter.displayResults();                  // 打印全部结果
    return 0;
}