//Heap test file

#include "hash.h"
#include "donut.h"
#include <iostream>
#include <vector>

using namespace std;

unsigned cyclic_hash16(string key);

int main() {

  Heap <Donut> h1;
  cout << "h1 created" << endl;

  Donut glazed = Donut("glazed",5,"super donut");
  Donut jesus = Donut("jesus", 8, "GOD");
  Donut strawberry = Donut("strawberry", 6, "straw");
  Donut blueberry = Donut("blueberry", 3, "blue");
  Donut chocolate = Donut("chocolate", 12, "choc");
  Donut glazed2 = Donut("glazed", 7, "donut super");
  Donut glazedcopy = Donut("lgazed", 15, "copy");
  cout << "insert test" << endl;
  h1.insert(glazed);
  h1.insert(jesus);
  h1.insert(strawberry);
  h1.insert(blueberry);
  h1.insert(chocolate);
  
  cout << "test heap return top" << endl;
  Donut hi =  h1.readTop();

  cout << hi << endl;

  cout << endl;


  cout << "dumping h1" << endl;
  h1.dump();

  cout << "Removing top" << endl;
  h1.removeTop();

  cout << endl;

  cout << "dumping h1" << endl;
  h1.dump();

  vector<Donut> donuts;
  donuts.push_back(glazed);
  donuts.push_back(jesus);
  donuts.push_back(strawberry);
  donuts.push_back(blueberry);
  donuts.push_back(glazed2);
  
  HashTable<Donut> ht(10,cyclic_hash16);


  for (auto d : donuts) {
    ht.insert(d);
  }

  cout << "\nDump of ht:\n";
  ht.dump();

  Donut d;
  vector<string> orders;

  orders.push_back("glazed");
  orders.push_back("strawberry");
  orders.push_back("glazed");
  
  for ( auto ord : orders ) {
    cout << "\nGet next '" << ord << "' order...\n";
    if ( ht.getNext(ord, d) ) {
      cout << "  " << d << endl;
    } else {
      cout << "  No " << ord << " orders!\n";
    }
  }

  cout << endl;

  cout << "\nDump of ht:\n";
  ht.dump();

  vector<string> orders2; 
  cout << "testing conditional" << endl;
  ht.insert(glazedcopy);

  cout << "\nDump of ht:\n";
  ht.dump();
  
}

unsigned cyclic_hash16(string key) {
  unsigned usize = 16;
  unsigned s = 5; // shift by 5
  unsigned h = 0;
  for (auto c : key) {
    h = (( h << s ) | ( h >> (usize - s) ));
    h += c;
    h = h & 0xffff;
  }
  return h;
}
