#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "MinQueue.h"
using namespace std;

int main()
{
    MinQueue<string> queue;
    for(int i = 10; i <= 100; i+=10)
    {
        stringstream ss;
        ss << i;
        queue.enqueue(ss.str());
    }
    cout << "Queue: " << endl;
    queue.print();
    cout << endl;
    cout << "Queue Size: ";
    cout << queue.size();
    cout << endl;
    queue.dequeue();
    cout << endl;
    cout << "Queue (After Dequeue): " << endl;
    queue.print();
    cout << endl;
    cout << "Queue Empty? ";
    cout << queue.is_empty();
    cout << endl;
    cout << "Smallest Value in Queue: ";
    cout << queue.min();
    cout << endl;
}