all: test_list.x proj2.x

test_list.x : test_list.cpp List.h
        g++ -std=c++11 test_list.cpp -o test_list.x

proj2.x : mem_manager.cpp mem_manager.h List.h List.hpp
        g++ -std=c++11 mem_manager.cpp -o proj2.x

clean:
        rm -f *.o *.x core.*
