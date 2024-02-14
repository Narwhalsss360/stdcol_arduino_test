#include <stdcol.h>

using stdcol::hash_table;

/*
    Hash tables work through hash codes, meaning there must be a way to turn
    the key to a number, create your own like this:
*/
using stdcol::hasher;
using stdcol::index;

struct String_hasher {
    /*
        One way to turn a string into a number is to get the
        sum of its ascii characters. This one is simple
    */
    index operator()(const String& str) const {
        index sum = 0;
        for (const char& c : str) {
            sum += c;
        }
        return sum;
    }
};

/*
    String to int using String_hasher
*/
hash_table<String, int, String_hasher> nameToAge;

void setup() {
    Serial.begin(115200);
    while (!Serial) {};
    Serial.println("START");

    //Add/changed name 1 to 35
    nameToAge["name 1"] = 25;

    nameToAge["name 2"] = 20;
    nameToAge["name 3"] = 15;
    nameToAge["name 4"] = 10;
    nameToAge["name 5"] = 5;

    //Check if name 1 exists in the hash_table
    if (nameToAge.contains("name 1")) {}

    stdcol::dynamic_array<String> keys = nameToAge.keys();
    stdcol::dynamic_array<int> values = nameToAge.values();
    hash_table<String, int, String_hasher>::buckets_t buckets = nameToAge.buckets();
    for (int iBucket = 0; iBucket < buckets.size(); iBucket++) {
        Serial.print("--- Bucket ");
        Serial.print(iBucket);
        Serial.println("---");

        for (int iPair = 0; iPair < buckets[iBucket].size(); iPair++) {
            Serial.print("    ");
            Serial.print(buckets[iBucket][iPair].key);
            Serial.print(": ");
            Serial.print(buckets[iBucket][iPair].value);
        }
        Serial.println();
    }
}

void loop() {

}