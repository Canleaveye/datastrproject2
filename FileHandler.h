#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

class FileHandler {
public:
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
            // 清洗停用词（转小写）
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            stopWords.insert(word);
            count++;
        }

        file.close();
        std::cout << "已加载 " << count << " 个停用词" << std::endl;
        return stopWords;
    }

    // 创建示例文章文件
    static bool createSampleArticle(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "无法创建文件: " << filename << std::endl;
            return false;
        }

        file << "The quick brown fox jumps over the lazy dog.\n";
        file << "This is a simple test article for word frequency analysis.\n";
        file << "The program should count each word and display the results.\n";
        file << "We can test with various words like apple, banana, orange, and grape.\n";
        file << "Repeated words help test the frequency counting functionality.\n";
        file << "The word 'the' appears multiple times in this text.\n";
        file << "So does 'word' and 'test' to check the counting accuracy.\n";
        file << "Programming is fun and challenging. It requires patience and practice.\n";
        file << "Data structures and algorithms are fundamental concepts in computer science.\n";
        file << "This system uses a red-black tree for efficient word storage and retrieval.\n";

        file.close();
        std::cout << "已创建示例文章: " << filename << std::endl;
        return true;
    }

    // 创建示例停用词文件
    static bool createSampleStopWords(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "无法创建文件: " << filename << std::endl;
            return false;
        }

        // 常用英文停用词
        file << "the\nand\na\nan\nis\nare\nin\non\nat\nto\nof\nfor\nwith\nby\n";
        file << "this\nthat\nit\nas\nor\nbut\nnot\nso\nif\nthen\nwhen\nwhere\n";
        file << "how\nwhy\nwhat\nwhich\nwho\nwhom\nwhose\n";

        file.close();
        std::cout << "已创建示例停用词表: " << filename << std::endl;
        return true;
    }

    // 获取文件大小
    static long getFileSize(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            return -1;
        }
        return file.tellg();
    }

    // 检查文件是否存在
    static bool fileExists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }
};

#endif // FILEHANDLER_H