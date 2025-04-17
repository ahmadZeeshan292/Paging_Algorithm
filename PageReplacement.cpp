#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cctype>

bool isfull(char arra[], int size) {
    for (int i = 0; i < size; i++) {
        if (arra[i] == '\0') {
            return false;
        }
    }
    return true;
}

int getfreeindex(char arra[], int size) {
    for (int i = 0; i < size; i++) {
        if (arra[i] == '\0') {
            return i;
        }
    }
    return -1;
}

int getindexchar(char arra[], int size, char val) {
    for (int i = 0; i < size; i++) {
        if (arra[i] == val) {
            return i;
        }
    }
    return -1;
}

bool currentpagepresent(char arra[], int size, char val) {
    for (int i = 0; i < size; i++) {
        if (arra[i] == val) {
            return true;
        }
    }
    return false;
}

void operator-(std::vector<char> a, std::vector<char>& b) {
    std::vector<char> ans;
    for (auto val : a) {
        if (std::find(b.begin(), b.end(), val) == b.end()) {
            ans.push_back(val);
        }
    }
    b = ans;
}

class PageReplacement {
public:
    PageReplacement(){}

    PageReplacement(const std::string& s, int table_size)
        : reference_string(s), page_table_size(table_size), page_faults(0) {
        parseReferenceString();
        page_table = new char[page_table_size]();
    }

    ~PageReplacement() {
        delete[] page_table;
    }

    bool step() {
        if (refernce_string.empty()) return false;

        auto it = refernce_string.begin();

        if (currentpagepresent(page_table, page_table_size, it->second)) {
            refernce_string.erase(it);
            return true;
        }

        if (!isfull(page_table, page_table_size)) {
            int index = getfreeindex(page_table, page_table_size);
            page_table[index] = it->second;
            refernce_string.erase(it);
        }
        else {
            auto iter = refernce_string.end();
            std::vector<char> a;
            while (iter != refernce_string.begin()) {
                if (a.size() == page_name.size()) break;

                --iter;
                if (std::find(a.begin(), a.end(), iter->second) == a.end()) {
                    a.push_back(iter->second);
                }
            }
            if (a.size() != page_name.size()) page_name - a;
            char victum = char();
            for (int i = a.size() - 1; i > -1; i--) {
                if (currentpagepresent(page_table, page_table_size, a[i])) {
                    victum = a[i];
                    break;
                }
            }
            int victum_page_index = getindexchar(page_table, page_table_size, victum);
            page_table[victum_page_index] = it->second;
            refernce_string.erase(it);
        }
        page_faults++;
        return true;
    }

    const char* getPageTable() const {
        return page_table;
    }

private:
    void parseReferenceString() {
        int i = 0;
        for (auto val : reference_string) {
            if (isdigit(val)) {
                refernce_string[i] = val;
                if (std::find(page_name.begin(), page_name.end(), val) == page_name.end()) {
                    page_name.push_back(val);
                }
                i++;
            }
        }
    }

    std::unordered_map<int, char> refernce_string;
    std::vector<char> page_name;
    std::string reference_string;
    int page_table_size;
    char* page_table;
    int page_faults;
};
