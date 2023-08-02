#ifndef DATABASE_H
#define DATABASE_H

# include <unordered_map>

template<typename T>
class Database {
    std::vector<std::tuple<T>> tuples;
    std::unordered_map<std::string, int> cols;
};

#endif