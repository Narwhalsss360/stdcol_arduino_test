#include <stdcol.h>

// Types overview

//Static size, just like int arr[].
using stdcol::array;

//Wrap around anything that uses [], fixed size.
using stdcol::wrapper;

//Dynamic size, just like [] but change change size.
using stdcol::dynamic_array;

//dynamic_array but cannot have more than one occurence of an element.
using stdcol::set;

//dynamic_array but use += and -= to push and pop on a stack.
using stdcol::stack;

//dynamic_array but use += and -= to enqueue and dequeue
using stdcol::queue;

//dynamic_array but use += { priority, item } and -= 
using stdcol::priority_queue;

//linked list where items can be emplaced.
using stdcol::linked;

void setup() {
    Serial.begin(115200);
    while (!Serial) {};
    Serial.println("START");

    array<int, 6> intArray = { 5, 10, 15, 20, 25, 30 };
    dynamic_array<int> dynamicInts;

    for (int& i : intArray) {
        dynamicInts.insert(dynamicInts.size(), i);
    }

    stack<int> s;
    for (int& i : intArray) {
        if (s += i) {
            Serial.print("Added ");
            Serial.print(i);
            Serial.println(" to stack");
        } else {
            Serial.println("There was an error adding an element to the stack");
        }
    }

    while (s.size()) {
        int item;
        if (s -= item) {
            Serial.print("Popped: ");
            Serial.println(item);
        } else {
            Serial.println("There was a problem popping from the stack");
        }
    }

    queue<int> q;
    for (int& i : intArray) {
        if (q += i) {
            Serial.print("Added ");
            Serial.print(i);
            Serial.println(" to the queue");
        } else {
            Serial.println("There was an error adding an element to the queue");
        }
    }

    while (q.size())
    {
        int item;
        if (q -= item) {
            Serial.print("Deqeued ");
            Serial.println(item);
        } else {
            Serial.println("There was a problem dequeueing");
        }
    }
}

void loop() {
}