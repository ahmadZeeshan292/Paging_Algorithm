#pragma once

#include <list>
#include <vector>
#include<string>
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>
#include <random>
#include <algorithm>

#define pg_len 4  // Number of pages per block
#define v_len 20  // Number of blocks in virtual memory

#define frame_len 4 // Number of pages per block
#define phy_len 20  // Number of blocks in physical memory

class Process {
    int size;

public:
    Process(int size) : size(size) {}

    int getSize() const {
        return size;
    }
};

template <class T>
struct page {
    T page_array[pg_len];

public:
    page() {
        for (int i = 0; i < pg_len; ++i) {
            page_array[i] = -1;
        }
    }
};

template <class T>
class virtual_memory {
    Process process;
    double no_pages;

public:
    page<T>* v_memory[v_len]; // dynamic int array 20x4 array 

    virtual_memory(int process_size) : process(process_size) {
        no_pages = 0;
        for (int i = 0; i < v_len; ++i) {
            v_memory[i] = new page<T>();
        }
        allocate_virtual_memory();
    }

    ~virtual_memory() {
        for (int i = 0; i < v_len; ++i) {
            delete v_memory[i];
        }
    }

    void allocate_virtual_memory() {
        int count = 0;
        no_pages = (process.getSize() + pg_len - 1) / pg_len; // Calculate the number of blocks needed

        if (no_pages > v_len) {
            //cout << "Error: Not enough virtual memory to accommodate the process." << endl;
            return;
        }
        if (no_pages < 4) {
            for (int j = 0; j < pg_len; j++) {
                if (count >= no_pages) {
                    break;
                }

                v_memory[0]->page_array[j] = count;
                count++;
            }

            return;
        }
        else {
            for (int i = 0; i < (no_pages / pg_len); i++) {
                for (int j = 0; j < pg_len; j++) {
                    if (count >= no_pages) {
                        break;
                    }
                    v_memory[i]->page_array[j] = count;
                    count++;
                }
            }
        }
    }

    void display_memory() const {
        for (int i = 0; i < v_len; i++) {
            cout << "Block " << i << endl;
            for (int j = 0; j < pg_len; j++) {
                cout << v_memory[i]->page_array[j] << " ";
            }
            cout << endl;
        }
    }

    int get_no_pages() const {
        return no_pages;
    }

    int calculate_internal_fragmentation() const {
        int total_internal_frag = 0;
        for (int i = 0; i < no_pages; i++) {
            int used_space = 0;
            for (int j = 0; j < pg_len; j++) {
                if (v_memory[i]->page_array[j] != -1) {
                    used_space++;
                }
            }
            total_internal_frag += (pg_len - used_space);
        }
        return total_internal_frag * 512; // Assuming each unit is 512 bytes
    }
};

class page_table_entry {
public:
    int vm_block_index;
    int pm_block_index;
    bool valid;

    page_table_entry(int vm_index, int pm_index, bool valid)
        : vm_block_index(vm_index), pm_block_index(pm_index), valid(valid) {}
};

template <class T>
class page_table {
public:
    std::list<page_table_entry> table;
    int physical_memory_size;

    page_table() : physical_memory_size(0){}

    page_table(int physical_memory_size) : physical_memory_size(physical_memory_size) {}

    void create_page_table(const virtual_memory<T>& vm) {
        int no_blocks = vm.get_no_pages();
        if (no_blocks > physical_memory_size) {
            //cout << "Error: Not enough physical memory to accommodate the process." << endl;
            return;
        }

        for (int i = 0; i < no_blocks; ++i) {
            int pm_index = i % physical_memory_size; // Simple mapping
            table.emplace_back(i, pm_index, true);
        }
    }

    void display_page_table() const {
        for (const auto& entry : table) {
            
        }
    }
};

template <class T>
struct frame {
    T frame_array[frame_len];

public:
    frame() {
        for (int i = 0; i < frame_len; ++i) {
            frame_array[i] = -1;
        }
    }
};

template <class T>
class physical_memory {
    page_table<T> obj;
    frame<T>* phy_memory[phy_len];

public:

    physical_memory(){
        for (int i = 0; i < phy_len; ++i) {
            phy_memory[i] = nullptr;
        }
    }

    physical_memory(const page_table<T>& pt) : obj(pt) {
        for (int i = 0; i < phy_len; ++i) {
            phy_memory[i] = nullptr;
        }
    }

    void allocate_physical_memory(const virtual_memory<T>& vm) {
        for (const auto& entry : obj.table) {
            int vm_block_index = entry.vm_block_index;
            int pm_block_index = entry.pm_block_index;

            if (pm_block_index >= 0 && pm_block_index < phy_len) {
                if (phy_memory[pm_block_index] == nullptr) {
                    phy_memory[pm_block_index] = new frame<T>();
                }

                for (int i = 0; i < frame_len; ++i) {
                    phy_memory[pm_block_index]->frame_array[i] = vm.v_memory[vm_block_index]->page_array[i];
                }
            }
        }
    }

    int get_page_table_size() { return obj.table.size(); }

    void display_physical_memory() const {
        for (int i = 0; i < phy_len; ++i) {
            cout << "Physical Memory Block " << i << ": ";
            if (phy_memory[i] != nullptr) {
                for (int j = 0; j < frame_len; ++j) {
                    cout << phy_memory[i]->frame_array[j] << " ";
                }
            }
            else {
                cout << "Empty";
            }
            cout << endl;
        }
    }

    frame<int>** get_phy_mem() {
        return phy_memory;
    }

    page_table<T> get_page_table() {
        return obj;
    }

    ~physical_memory() {
        for (int i = 0; i < phy_len; ++i) {
            delete phy_memory[i];
        }
    }
};

char getRandomLocation(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, size);
    return dist(gen);
}

std::vector<int> generate_reference_string(int length, int max_page) {
    std::vector<int> ref_string(length);
    for (int i = 0; i < length; ++i) {
        ref_string[i] = getRandomLocation(max_page);
    }
    return ref_string;
}

bool currentpagepresent(std::vector<int> arra, int size, int val) {
    for (int i = 0; i < size; i++) {
        if (arra[i] == val) {
            return true;
        }
    }
    return false;
}

bool isfull(std::vector<int> arra, int size) {
    for (int i = 0; i < size; i++) {
        if (arra[i] == -1) {  // Initialize empty slots with -1 instead of '\0'
            return false;
        }
    }
    return true;
}

int getfreeindex(std::vector<int> arra, int size) {
    for (int i = 0; i < size; i++) {
        if (arra[i] == -1) {  // Initialize empty slots with -1 instead of '\0'
            return i;
        }
    }
    return -1;
}

int getindexchar(std::vector<int> arra, int size, int val) {
    for (int i = 0; i < size; i++) {
        if (arra[i] == val) {
            return i;
        }
    }
    return -1;
}

void subtract_vectors(std::vector<int> a, std::vector<int>& b) {
    std::vector<int> ans;
    for (auto val : a) {
        if (std::find(b.begin(), b.end(), val) == b.end()) {
            ans.push_back(val);
        }
    }
    b = ans;
}
// create an array condition if array.size() == page_table.size()-1 break; if the value is in the array all good else the value which s not is the victum proceess
class PageReplacement {
public:
    PageReplacement() :  page_table_size(0), page_faults(0) {}

    PageReplacement(const std::vector<int>& s, int table_size)
        : reference_string(s), page_table_size(table_size), page_faults(0) {
        parseReferenceString();
        page_table.resize(page_table_size);
        std::fill(page_table.begin(), page_table.end(), -1);
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
            auto iter = prev(refernce_string.end());
            std::vector<int> a;
            while (iter != refernce_string.begin()) {
                if (a.size() == page_table_size - 1) break;

                if (currentpagepresent(page_table, page_table_size, iter->second))
                    a.push_back(iter->second);
                --iter;
            }
            if (a.size() != page_name.size()) subtract_vectors(page_name, a);

            int victum = -1;
            for (int i = 0; i < a.size(); i++) {
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

    std::vector<int>& getPageTable() {
        return page_table;
    }

    int gettablesize() {
        return page_table_size;
    }

    int getReferenceStringSize() {
        return refernce_string.size();
    }

    int getinitialsize() {
        return reference_string.size();
    }

    int getpagefaults() {
        return page_faults;
    }

    std::string getreferencestring() {
        std::string s;
        for (int i = 0;i < reference_string.size();i++) {
            s += std::to_string(reference_string[i]);
        }
        return s;
    }

private:
    void parseReferenceString() {
        int i = 0;
        for (auto val : reference_string) {
            refernce_string[i] = val;
            if (std::find(page_name.begin(), page_name.end(), val) == page_name.end()) {
                page_name.push_back(val);
            }
            i++;
        }
    }

    std::hash_map<int, int> refernce_string;
    std::vector<int> page_name;
    std::vector<int> reference_string;
    int page_table_size;
    std::vector<int> page_table;
    int page_faults;
};
