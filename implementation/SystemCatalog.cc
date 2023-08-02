#include "../include/SystemCatalog.h"

void SystemCatalog::createTable(const std::string& tableName, const std::vector<std::string> & columns) {
    
}

void SystemCatalog::createIndex(const std::string& tableName, const std::string& columnName, int indexType) {
    tables[tableName].indexedColumns[columnName] = indexType;
}