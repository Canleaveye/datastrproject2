#ifndef DATAANALYZER_H
#define DATAANALYZER_H

#include "RedBlackTree.h"
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <iomanip>
#include <functional>
#include <limits>
#include <iostream>
#include <sstream>
#include <cctype>

class DataAnalyzer {
private:
    // 自定义排序比较器：按频率降序，相同频率按字母升序
    struct WordFrequencyComparator {
        bool operator()(const std::pair<std::string, int>& a,
            const std::pair<std::string, int>& b) const {
            if (a.second == b.second) {
                return a.first < b.first;  // 频率相同，按字母顺序
            }
            return a.second > b.second;    // 按频率降序
        }
    };

public:
    // 从文件读取并统计词频
    static RedBlackTree<std::string, int> analyzeFile(const std::string& filename) {
        RedBlackTree<std::string, int> wordFreq;

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "错误：无法打开文件 " << filename << std::endl;
            return wordFreq;
        }

        std::cout << "正在分析文件: " << filename << std::endl;

        std::string word;
        int totalWords = 0;

        while (file >> word) {
            // 清洗单词：去除标点，转为小写
            std::string cleanWord;
            for (char ch : word) {
                if (std::isalpha(static_cast<unsigned char>(ch))) {
                    cleanWord += std::tolower(static_cast<unsigned char>(ch));
                }
            }

            if (!cleanWord.empty()) {
                // 检查单词是否已存在
                int* existingFreq = wordFreq.find(cleanWord);
                if (existingFreq) {
                    // 如果存在，增加频率
                    wordFreq.modify(cleanWord, *existingFreq + 1);
                }
                else {
                    // 如果不存在，插入新单词
                    wordFreq.insert(cleanWord, 1);
                }
                totalWords++;
            }
        }

        file.close();

        std::cout << "分析完成！" << std::endl;
        std::cout << "总单词数: " << totalWords << std::endl;
        std::cout << "不同单词数: " << wordFreq.size() << std::endl;

        return wordFreq;
    }

    // 从字符串文本分析词频
    static RedBlackTree<std::string, int> analyzeText(const std::string& text) {
        RedBlackTree<std::string, int> wordFreq;

        std::istringstream iss(text);
        std::string word;
        int totalWords = 0;

        while (iss >> word) {
            // 清洗单词：去除标点，转为小写
            std::string cleanWord;
            for (char ch : word) {
                if (std::isalpha(static_cast<unsigned char>(ch))) {
                    cleanWord += std::tolower(static_cast<unsigned char>(ch));
                }
            }

            if (!cleanWord.empty()) {
                // 检查单词是否已存在
                int* existingFreq = wordFreq.find(cleanWord);
                if (existingFreq) {
                    // 如果存在，增加频率
                    wordFreq.modify(cleanWord, *existingFreq + 1);
                }
                else {
                    // 如果不存在，插入新单词
                    wordFreq.insert(cleanWord, 1);
                }
                totalWords++;
            }
        }

        std::cout << "文本分析完成！" << std::endl;
        std::cout << "总单词数: " << totalWords << std::endl;
        std::cout << "不同单词数: " << wordFreq.size() << std::endl;

        return wordFreq;
    }

    //红黑树按Key排序，转换为按Value排序
    static std::vector<std::pair<std::string, int>>
        sortByFrequency(const RedBlackTree<std::string, int>& wordFreq,
            const std::unordered_set<std::string>& stopWords = {}) {

        std::vector<std::pair<std::string, int>> result;

        // 使用红黑树的getAll()方法获取所有数据
        auto allData = wordFreq.getAll();

        //高效过滤停用词（O(1)查找）
        for (const auto& pair : allData) {
            if (stopWords.find(pair.first) == stopWords.end()) {
                result.push_back(pair);
            }
        }

        // 自定义排序算法
        std::sort(result.begin(), result.end(), WordFrequencyComparator());

        return result;
    }

    // 获取Top N高频词
    static std::vector<std::pair<std::string, int>>
        getTopN(const RedBlackTree<std::string, int>& wordFreq,
            int N = 10,
            const std::unordered_set<std::string>& stopWords = {}) {

        auto sortedWords = sortByFrequency(wordFreq, stopWords);

        if (N > static_cast<int>(sortedWords.size())) {
            N = sortedWords.size();
        }

        return std::vector<std::pair<std::string, int>>(
            sortedWords.begin(), sortedWords.begin() + N);
    }

    // 显示Top N高频词（精美表格）
    static void displayTopN(const RedBlackTree<std::string, int>& wordFreq,
        int N = 10,
        const std::unordered_set<std::string>& stopWords = {}) {

        auto sortedWords = sortByFrequency(wordFreq, stopWords);

        if (sortedWords.empty()) {
            std::cout << "没有可显示的数据！" << std::endl;
            return;
        }

        N = std::min(N, static_cast<int>(sortedWords.size()));

        // 计算Top N的总词频
        int totalTopN = 0;
        for (int i = 0; i < N; i++) {
            totalTopN += sortedWords[i].second;
        }

        // 表格输出
        std::cout << "\n+----------------------------------------------------------+\n";
        std::cout << "|                    Top " << std::setw(2) << N << " 高频词统计                |\n";
        std::cout << "+----------------------------------------------------------+\n";
        std::cout << "| 排名 | 单词                | 出现次数 | 频率占比       |\n";
        std::cout << "+----------------------------------------------------------+\n";

        for (int i = 0; i < N; i++) {
            double percentage = 100.0 * sortedWords[i].second / totalTopN;

            std::cout << "| " << std::setw(4) << i + 1 << " | "
                << std::left << std::setw(18) << sortedWords[i].first << " | "
                << std::right << std::setw(6) << sortedWords[i].second << " 次 | "
                << std::fixed << std::setprecision(2) << std::setw(8)
                << percentage << "% |" << std::endl;
        }

        std::cout << "+----------------------------------------------------------+\n";

        // 统计信息
        std::cout << "\n[统计信息]\n";
        std::cout << "显示单词数: " << N << "/" << wordFreq.size() << "\n";
        std::cout << "Top " << N << " 总词频: " << totalTopN << "\n";
        std::cout << "最高频词: " << sortedWords[0].first << " (" << sortedWords[0].second << "次)\n";
        std::cout << "停用词过滤: " << (stopWords.empty() ? "无" : "已启用") << "\n";
    }

    // 保存结果到文件
    static bool saveResultsToFile(const RedBlackTree<std::string, int>& wordFreq,
        const std::string& filename = "results.txt",
        int N = 20,
        const std::unordered_set<std::string>& stopWords = {}) {

        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "错误：无法创建文件 " << filename << std::endl;
            return false;
        }

        auto results = getTopN(wordFreq, N, stopWords);

        // 计算总词频用于百分比
        int totalFreq = 0;
        for (const auto& item : results) {
            totalFreq += item.second;
        }

        // 写入文件头
        outFile << "================================================\n";
        outFile << "          词频统计结果\n";
        outFile << "================================================\n\n";

        outFile << "统计概要:\n";
        outFile << "统计时间: " << __DATE__ << " " << __TIME__ << "\n";
        outFile << "不同单词数: " << wordFreq.size() << "\n";
        outFile << "停用词过滤: " << (stopWords.empty() ? "无" : "已启用") << "\n";
        outFile << "显示单词数: " << results.size() << "\n\n";

        // 写入词频表
        outFile << "词频排名（按频率降序）:\n";
        outFile << "排名,单词,出现次数,频率占比\n";

        for (size_t i = 0; i < results.size(); i++) {
            double percentage = (totalFreq > 0) ? 100.0 * results[i].second / totalFreq : 0.0;
            outFile << i + 1 << ","
                << results[i].first << ","
                << results[i].second << ","
                << std::fixed << std::setprecision(2) << percentage << "%\n";
        }

        outFile << "\n================================================\n";
        outFile << "基于红黑树的词频统计系统\n";

        outFile.close();
        std::cout << "结果已保存到: " << filename << std::endl;
        return true;
    }

    // 从文件加载停用词表
    static std::unordered_set<std::string> loadStopWords(const std::string& filename) {
        std::unordered_set<std::string> stopWords;

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "提示：未找到停用词文件 " << filename << std::endl;
            return stopWords;
        }

        std::string word;
        int count = 0;
        while (file >> word) {
            // 转小写
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            stopWords.insert(word);
            count++;
        }

        file.close();
        std::cout << "已加载 " << count << " 个停用词" << std::endl;
        return stopWords;
    }

    // 生成测试数据
    static RedBlackTree<std::string, int> createTestData() {
        RedBlackTree<std::string, int> testData;

        // 一些测试数据
        testData.insert("programming", 45);
        testData.insert("algorithm", 38);
        testData.insert("data", 32);
        testData.insert("structure", 28);
        testData.insert("computer", 25);
        testData.insert("science", 22);
        testData.insert("code", 18);
        testData.insert("test", 15);
        testData.insert("analysis", 12);
        testData.insert("system", 10);
        testData.insert("the", 60);   // 停用词
        testData.insert("and", 45);   // 停用词
        testData.insert("is", 30);    // 停用词
        testData.insert("a", 25);     // 停用词

        return testData;
    }
};

#endif // DATAANALYZER_H