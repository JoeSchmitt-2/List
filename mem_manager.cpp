#include <iostream>                                                                                                               mem_manager.cpp                                                                                     0000600 0266275 0000453 00000004332 14012115214 014003  0                                                                                                    ustar   jschmitt                        CS-Grads                                                                                                                                                                                                               #include <iostream>
#include <string>
#include "List.h"
#include "mem_manager.h"
using namespace std;
using namespace cop4530;
/*
        Joseph Schmitt
        COP4530
*/

void print_menu() {
    cout << "d: memory dump" << endl;
    cout << "r: request memory" << endl;
    cout << "l: release memory" << endl;
    cout << "m: merge memory" << endl;
    cout << "x: quit program" << endl;
    cout << "Your choice: ";
}

//*************************************
//Start of MyMemoryBlock
MyMemoryBlock::MyMemoryBlock(int ind, int len) : index { ind }, length { len }
{ }

int MyMemoryBlock::get_length()
{
    return length;
}

int MyMemoryBlock::get_index()
{
    return index;
}

int MyMemoryBlock::allocate_mem(int len)
{
    return length = length - len;
}

void MyMemoryBlock::free_mem(int len)
{
    length = length + len;
}

//**************************************************
//Start of MyMemory

MyMemory::MyMemory(int num, int len)
{
    max_index = num - 1;
    block_size = len;

    for (int i = 0; i < max_index; i++)
    {
        mlist.push_back(MyMemoryBlock(i, len));
    }
}

void MyMemory::resize(int num, int len)
{
    if(!mlist.empty())
    {
        mlist.clear();
    }
    max_index = num - 1;
    block_size = len;
}

int MyMemory::req_mem(int len)
{
    for(auto itr = mlist.begin(); itr != mlist.end(); itr++)
    {

    }

}

bool MyMemory::release_mem(int ind, int len)
{
    return false;
}

void MyMemory::merge_mem()
{

}

void MyMemory::dump()
{

}

MyMemory::~MyMemory()
{

}

int main()
{
    MyMemory a;
    int temp1, temp2;
    cop4530::List<MyMemoryBlock> mlist;
    cout << "Memory configuration: " << endl;
    cout << "Number of memory blocks (integer): ";
    cin >> temp1;
    cout << "Memory block size (integer):";
    cin >> temp2;
    MyMemoryBlock(temp1, temp2);

    char choice;
    print_menu();
    cin >> choice;
    cout << "Choice: " << choice << endl;
    while(choice != 'x' || choice != 'X')
    {
        if(choice == 'd')
        {
            a.dump();
        }
        if(choice == 'r')
        {
            cout << "Requested memory size (integer): ";
            cin >> temp1;
        }
        if(choice == 'l');
        if(choice == 'm');
        if(choice == 'x')
            break;
    }


}
