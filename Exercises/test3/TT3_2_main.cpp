/*
2. 第四章 判断链串对称性
【问题描述】假设字符串 s 采用链串存储（即使用链表存储字符串），设计一个算法，判断它是否为 "x@x" 形式的字符串，其中 x 是不包含字符 '@' 的任意字符串。

【输入形式】输入一个字符串 s，其中 s 由字符串和 @ 组成（可能含有@）。

【输出形式】如果 s 为 "x@x" 形式，输出 true；否则输出 false。

【样例输入】

ab@ab

【样例输出】

true

【样例说明】
【评分标准】

【说明】

要求用链串设计，可以使用STL库函数。
*/

#include <iostream>
#include <string>
#include <cstddef>

class myString {
public:
	myString() : headNode('\0'), tailNode(&headNode), size(0) {}

	explicit myString(const char *cstr) : headNode('\0'), tailNode(&headNode), size(0) {
		assign(cstr);
	}

	~myString() {
		clear();
	}

	void pushBack(char ch) {
		Node *newNode = new Node(ch);
		tailNode->next = newNode;
		tailNode = newNode;
		++size;
	}

	void clear() {
		Node *current = headNode.next;
		while (current != nullptr) {
			Node *next = current->next;
			delete current;
			current = next;
		}
		headNode.next = nullptr;
		tailNode = &headNode;
		size = 0;
	}

	void assign(const char *cstr) {
		clear();
		append(cstr);
	}

	void append(const char *cstr) {
		if (cstr == nullptr) {
			return;
		}
		while (*cstr != '\0') {
			pushBack(*cstr);
			++cstr;
		}
	}

	int findFirst(char ch) const {
		Node *current = headNode.next;
		int pos = 1;
		while (current != nullptr) {
			if (current->value == ch) {
				return pos;
			}
			current = current->next;
			++pos;
		}
		return -1;
	}

	char at(size_t index) const {
		if (index >= size) {
			return '\0';
		}
		Node *current = headNode.next;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}
		return current->value;
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

private:
	struct Node {
		char value;
		Node *next;
		explicit Node(char v) : value(v), next(nullptr) {}
	};
	Node headNode;
	Node *tailNode;
	size_t size;
};


int main() {
    std::string input;
    std::getline(std::cin, input);
    myString s(input.c_str());

    int atPos = s.findFirst('@');
    if (atPos == -1) {
        std::cout << "false" << std::endl;
        return 0;
    }

    int countAt = 0;
    for (size_t i = 0; i < s.getSize(); ++i) {
        if (s.at(i) == '@') {
            ++countAt;
        }
    }
    if (countAt != 1) {
        std::cout << "false" << std::endl;
        return 0;
    }

    size_t leftLen = atPos - 1;
    size_t rightLen = s.getSize() - atPos;
    if (leftLen != rightLen) {
        std::cout << "false" << std::endl;
        return 0;
    }

    for (size_t i = 0; i < leftLen; ++i) {
        if (s.at(i) != s.at(atPos + i)) {
            std::cout << "false" << std::endl;
            return 0;
        }
    }

    std::cout << "true" << std::endl;
    return 0;
}