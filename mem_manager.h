#include "List.h"                                                                                                                                                                                                                                                                                                                                                          mem_manager.h                                                                                       0000600 0266275 0000453 00000001154 14012112705 013451  0                                                                                                    ustar   jschmitt                        CS-Grads                                                                                                                                                                                                               #include "List.h"
using namespace cop4530;
/*
        Joseph Schmitt
        COP4530
*/

class MyMemoryBlock
{
public:
    MyMemoryBlock(int ind = 0, int len = 0);
    int get_length();
    int get_index();
    int allocate_mem(int len);
    void free_mem(int len);
private:
    int index, length;
};

class MyMemory
{
public:
    MyMemory(int num = 0, int len = 0);
    void resize(int num = 100, int len = 100);
    int req_mem(int len);
    bool release_mem(int ind, int len);
    void merge_mem();
    void dump();
    ~MyMemory();
private:
    cop4530::List<MyMemoryBlock> mlist;
    int max_index, block_size;
};
