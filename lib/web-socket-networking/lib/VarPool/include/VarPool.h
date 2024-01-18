#pragma once

#include <unordered_map>
#include <iterator>
#include <map>
#include <any>
#include <string>
#include <optional>
#include <vector>
#include <functional>
#include "json.hpp"
using json = nlohmann::json;

class VarPool
{

public:
    VarPool();

    void addJson(json j);
    void addVar(const std::string &name, std::any value);

    std::string getType(const std::string &);
    bool exists(const std::string &);

    // getters
    //all the queries are able to answer abc.def.ghi queries (nested objects)
    std::optional<std::reference_wrapper<int>> getInt(const std::string &);

    std::optional<std::reference_wrapper<bool>> getBool(const std::string &);

    std::optional<std::reference_wrapper<double>> getDouble(const std::string &);

    std::optional<std::reference_wrapper<std::string>> getString(const std::string &);

    std::optional<std::reference_wrapper<std::vector<int>>> getIntList(const std::string &);

    std::optional<std::reference_wrapper<std::vector<double>>> getDoubleList(const std::string &);

    std::optional<std::reference_wrapper<std::vector<std::string>>> getStringList(const std::string &);

    std::optional<std::reference_wrapper<std::vector<VarPool>>> getList(const std::string &);

    //gets the default value if any
    template <class T>
    std::optional<std::reference_wrapper<T>> getVarPoolValue(const std::string &name);

    void removeVar(const std::string &);

    void setVar(const std::string &name, const std::any value);

private:
    std::unordered_map<std::string, std::any> pool;
    // The map's operator[] will insert a new element if the key isn't found, so the key must be non-const.

    // if the passed string is abc.hello.world, it will return {abc , hello.world}
    // if the passed string is abc, it will return {abc , ""}
    std::pair<std::string, std::string> split_key(const std::string &);
    
    //there can be nested varpools
    std::optional<std::reference_wrapper<VarPool>> getVarPool(const std::string &);
};

template <class T>
std::optional<std::reference_wrapper<T>> VarPool::getVarPoolValue(const std::string &name)
{
    if (!exists(name))
    {
        return std::nullopt;
    }

    try
    {
        std::reference_wrapper<T> ref = std::any_cast<T &>(pool[name]);
        return std::optional<std::reference_wrapper<T>>{ref};
    }
    catch (const std::bad_any_cast &e)
    {
        return std::nullopt;
    }
}

// void VarPool::setVar(const std::string &name, const std::any value)
// {
//     pool[name] = value;
// }
