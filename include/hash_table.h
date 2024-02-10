#ifndef hash_table_h
#define hash_table_h

#include "dictionary.h"

namespace stdcol {
    template <typename hashable_t, typename collectable_t, typename hasher_t = hasher<hashable_t>>
    class hash_table : public dictionary<hashable_t, collectable_t> {
    public:
        using dictionary = dictionary<hashable_t, collectable_t>;

        hash_table() : table_buckets(dictionary::buckets_t(11)), key_hasher(hasher_t()) {}

        hash_table(index size) : table_buckets(dictionary::buckets_t(size)), key_hasher(hasher_t()) {}

        bool contains(const hashable_t& key) override {
            for (const dictionary::kvp_t& kvp : bucket(key)) {
                if (kvp.key == key) {
                    return true;
                }
            }
            return false;
        }

        bool add(const hashable_t& key, const collectable_t& value) override {
            linked<key_value_pair<hashable_t, collectable_t>>& key_bucket = bucket(key);
            for (key_value_pair<hashable_t, collectable_t>& kvp : key_bucket) {
                if (kvp.key == key) {
                    kvp.value = value;
                    return true;
                }
            }

            return key_bucket.insert(0, { key, value });
        }

        bool remove(const hashable_t& key) override {
            linked<key_value_pair<hashable_t, collectable_t>>& key_bucket = bucket(key);
            for (auto ekvp : enumerate(key_bucket)) {
                if (ekvp.value.key == key) {
                    return key_bucket.remove(ekvp.index);
                }
            }
            return true;
        }

        bool resize(index bucket_count) override {
            dictionary::buckets_t new_buckets = dictionary::buckets_t(bucket_count);
            if (new_buckets.capacity() != bucket_count) {
                return false;
            }
            return true;
        }

        dictionary::kvp_t* get(const hashable_t& key) {
            for (dictionary::kvp_t& kvp : bucket(key)) {
                if (kvp.key == key) {
                    return & kvp;
                }
            }
            return nullptr;
        }

        collectable_t& get_add(const hashable_t& key) {
            dictionary::bucket_t& key_bucket = bucket(key);
             for (dictionary::kvp_t& kvp : key_bucket) {
                if (kvp.key == key) {
                    return kvp.value;
                }
            }

            if (key_bucket.insert(0, { key, collectable_t() })) {
                return key_bucket[0].value;
            }

            //Only gets here if adding was not possible, dereference nullptr for now, find alternative later.
            return *(collectable_t*)nullptr;
        }

        dictionary::buckets_t& buckets() override {
            return table_buckets;
        }

        dictionary::bucket_t& bucket(const hashable_t& hashable) override {
            return table_buckets[hash(hashable) % table_buckets.capacity()];
        }

        index hash(const hashable_t& key) override {
            return key_hasher(key);
        }

    protected:
        dictionary::buckets_t table_buckets;
        hasher_t key_hasher;
    };
}

#endif
