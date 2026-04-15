/*
1. 图书馆借阅记录
【问题描述】

       有一个大学图书馆借阅记录文件，第一行为整数n，表示有n个读者，每行包括读者编号、读者姓名、所在学院。接下来为整数m，表示有m本图书的信息，每行包括图书编号、书名和出版社。再接下来为整数k，表示有k条借阅记录，每行包括读者编号、图书编号和借阅日期（格式为YYYYMMDD）。编写程序分学院按读者编号递增排序输出所有借阅记录，同一读者按借阅日期递增排序，并输出读者编号、读者姓名、图书名称、出版社名称，借阅日期，注意相同的读者信息不重复输出。

【输入形式】

      第一行为整数n，表示有n个读者，每行包括读者编号、读者姓名、所在学院。接下来为整数m，表示有m本图书的信息，每行包括图书编号、书名和出版社。再接下来为整数k，表示有k条借阅记录，每行包括读者编号、图书编号和借阅日期（格式为YYYYMMDD）。 


【输出形式】

      第一行输出“学院：”后面跟着学院名称，下面几行输出相应的读者编号、姓名、图书名、出版社名、借阅日期。接着输出第二个“学院：“。

【样例输入】

3

1 张三 计算机学院

3 李四 遥感学院

5 王五 计算机学院

2

2 数据结构 清华大学出版社

1 C++语言程序设计 武汉大学出版社

4

1 1 20250602

5 2 20250213

3 2 20250708

5 1 20251009


【样例输出】

学院:计算机学院

1       张三    C++语言程序设计 武汉大学出版社  20250602

5       王五    数据结构        清华大学出版社  20250213

                    C++语言程序设计 武汉大学出版社  20251009

学院:遥感学院

3       李四    数据结构        清华大学出版社  20250708

【样例说明】

    输入输出为标准输出


【评分标准】

   允许使用STL  
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct Reader {
    int id;
    std::string name;
    std::string college;
};

struct Book {
    int id;
    std::string title;
    std::string publisher;
};

struct BorrowRecord {
    int readerId;
    int bookId;
    std::string date;
};

bool operator<(const Reader& a, const Reader& b) {
    if (a.college != b.college) {
        return a.college < b.college;   // 先按学院排序:string的<运算符会按字典序比较
    }
    return a.id < b.id;
}

bool operator<(const BorrowRecord& a, const BorrowRecord& b) {
    return a.date < b.date; // 按借阅日期排序,字符串比较会按字典序比较，日期格式为YYYYMMDD，字典序比较正好符合日期顺序
}

bool operator<(const Book& a, const Book& b) {
    return a.id < b.id; // 按图书编号排序
}

int main() {
    // 读入读者、图书和借阅记录
    int n;
    std::cin >> n;
    std::vector<Reader> readers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> readers[i].id >> readers[i].name >> readers[i].college;
    }

    int m;
    std::cin >> m;
    std::vector<Book> books(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> books[i].id >> books[i].title >> books[i].publisher;
    }

    int k;
    std::cin >> k;
    std::vector<BorrowRecord> records(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> records[i].readerId >> records[i].bookId >> records[i].date;
    }

    // 排序
    std::sort(readers.begin(), readers.end());
    std::sort(books.begin(), books.end());
    std::sort(records.begin(), records.end());

    // 输出结果
    std::string currentCollege;
    for (const auto& reader : readers) {
        if (reader.college != currentCollege) {
            currentCollege = reader.college;
            std::cout << "学院:" << currentCollege << "\n";
        }
        std::cout << reader.id << "\t" << reader.name << "\t";
        bool firstRecord = true;
        for (const auto& record : records) {
            if (record.readerId == reader.id) {
                const auto& book = books[record.bookId - 1]; // 索引 = bookId - 1
                if (!firstRecord) {
                    std::cout << "\t\t"; // 同一读者的后续记录缩进
                }
                std::cout << book.title << "\t" << book.publisher << "\t" 
                          << record.date << "\n";
                firstRecord = false;
            }
        }
    }


    return 0;
}