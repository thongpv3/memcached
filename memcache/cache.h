#include <core/sstring.hh>
#include <list>


using item_key = std::string;
using item_data = std::string;
struct expiration {

};


struct remote_origin_tag {
    template <typename T>
    static inline
    T move_if_local(T& ref) {
        return ref;
    }
};

struct local_origin_tag {
    template <typename T>
    static inline
    T move_if_local(T& ref) {
        return std::move(ref);
    }
};


class item {
    expiration _expiry;
    item_key key;
    item_data data;
};

struct item_insertion_data {
    item_key key;

};

class cache {
public:
    using cache_type = std::unordered_map<item_key, item>;
    using cache_iterator = cache_type::iterator;
    using allocator_type = cache_type::allocator_type;
private:
    cache_type _cache;
    std::list<item_key> _lru;

    template<bool IsInCache=true, bool IsInTimmerList= true>
    void erase(item_key& item_key) {
        if (IsInCache)
            _cache.erase(item_key);
        if (IsInTimmerList) {
            //todo implements
        }
    }

    cache_iterator find(const item_key& item_key) {
        return _cache.find(item_key);
    }


    template <typename Origin>
    cache_iterator add_overriding(item_key &key, item_insertion_data& data) {

    }

    template <typename Origin>
    cache_iterator add_new(item_key &key, item_insertion_data& data) {

    }
public:
    cache() {
    }


    bool set(item_insertion_data& insertion) {
        auto i = find(insertion.key);
        if (i != _cache.end()) {

        }
    }
};

class shared_cache {

};

class tcp_server {

};

class udp_server {

};