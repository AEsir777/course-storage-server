#ifndef SYSTEMCATALOG_H
#define SYSTEMCATALOG_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

class TableMetadata {
    std::string name;
    std::vector<std::string> colomns;
    // Stores column and type of index (B+ Tree, Hash, etc.)
    // 0: B+, 1 hash
    std::unordered_map<std::string, int> indexedColumns;  

    TableMetadata(std::string &name, std::vector<std::string>);

    friend class SystemCatalog;
};

class SystemCatalog {
private:
    std::unordered_map<std::string, TableMetadata> tables;
public:
    void createTable(const std::string& tableName, const std::vector<std::string> & columns);

    void createIndex(const std::string& tableName, const std::string& columnName, int indexType);

    bool hasIndex(const std::string& tableName, const std::string& columnName);
    
    int getIndexType(const std::string& tableName, const std::string& columnName);
};

#endif