CXX = g++
CXXFLAGS = -Wall

proj5: heap.h hash.h donut.h driver.cpp 
	$(CXX) $(CXXFLAGS) hash.h heap.h driver.cpp donut.h -o proj5

heap: heap.h hash.h donut.h testHeap.cpp
	$(CXX) $(CXXFLAGS) hash.h donut.h heap.h testHeap.cpp -o testHeap


clean:
	rm 
	rm *~

run:
	./proj5

valrun:
	valgrind ./proj5

testheap:
	./testHeap

valheap:
	valgrind ./testHeap
