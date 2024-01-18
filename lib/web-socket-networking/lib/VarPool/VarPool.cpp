#include "VarPool.h"
#include <sstream>
#include <iostream>
#include <any>

VarPool::VarPool()
{
}

// if the passed string is abc.hello.world, it will return {abc , hello.world}
// if the passed string is abc, it will return {abc , ""}
std::pair<std::string, std::string> VarPool::split_key(const std::string &str)
{

    std::string key = "";
    std::string rest = "";
    bool found = false;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '.' && !found)
        {
            found = true;
            continue;
        }
        if (!found)
        {
            key += str[i];
        }
        else
        {
            rest += str[i];
        }
    }
    return std::make_pair(key, rest);
}

// there can be nested varpools
std::optional<std::reference_wrapper<VarPool>> VarPool::getVarPool(const std::string &key)
{
    if (exists(key))
    {
        return std::any_cast<VarPool &>(pool[key]);
    }
    return std::nullopt;
}

// recursively adds json to the pool
void VarPool::addJson(json j)
{
    if (j.is_primitive())
    {

        if (j.is_boolean())
        {
            addVar("default", j.get<bool>());
        }
        else if (j.is_number_float())
        {
            addVar("default", j.get<double>());
        }
        else if (j.is_number_integer())
        {
            addVar("default", j.get<int>());
        }
        else if (j.is_string())
        {
            addVar("default", j.get<std::string>());
        }

        return;
    }

    for (json::iterator it = j.begin(); it != j.end(); ++it)
    {
        std::string key = it.key();
        auto value = it.value();

        if (value.is_primitive())
        {
            if (value.is_boolean())
            {
                addVar(key, value.get<bool>());
            }
            else if (value.is_number_integer())
            {
                addVar(key, value.get<int>());
            }
            else if (value.is_number_float())
            {
                addVar(key, value.get<double>());
            }
            else if (value.is_string())
            {
                addVar(key, value.get<std::string>());
            }
        }
        else if (value.is_array())
        {
            std::vector<VarPool> varPoolList;
            for (auto &element : value)
            {
                VarPool varPool;
                varPool.addJson(element);
                varPoolList.push_back(std::move(varPool));
            }
            addVar(key, varPoolList);
        }
        else if (value.is_object())
        {
            VarPool varPool;
            varPool.addJson(value);
            addVar(key, std::move(varPool));
        }
    }
}

void VarPool::addVar(const std::string &name, std::any value)
{
    pool[name] = value;
}

std::string VarPool::getType(const std::string &name)
{

    auto it = split_key(name);

    if (it.second == "")
    {
        if (pool.find(it.first) != pool.end())
        {
            return pool[it.first].type().name();
        }
        return "null";
    }
    else
    {
        if (pool.find(it.first) != pool.end())
        {
            if (pool[it.first].type() == typeid(VarPool))
            {
                return std::any_cast<VarPool &>(pool[it.first]).getType(it.second);
            }
        }
        return "null";
    }
}

bool VarPool::exists(const std::string &name)
{
    return pool.find(name) != pool.end();
}

// getters
std::optional<std::reference_wrapper<int>> VarPool::getInt(const std::string &name)
{

    auto it = split_key(name);

    if (!it.second.empty())
    {
        if (pool.find(it.first) != pool.end())
        {
            if (pool[it.first].type() == typeid(VarPool))
            {
                return std::any_cast<VarPool &>(pool[it.first]).getInt(it.second);
            }
        }
        return std::nullopt;
    }

    if (!exists(name))
        return std::nullopt;

    try
    {

        std::reference_wrapper<int> ref = std::any_cast<int &>(pool[name]);

        return std::optional<std::reference_wrapper<int>>{ref};
    }
    catch (const std::bad_any_cast &e)
    {
        return std::nullopt;
    }
}
std::optional<std::reference_wrapper<bool>> VarPool::getBool(const std::string &name)
{

    auto it = split_key(name);

    if (!it.second.empty())
    {
        if (pool.find(it.first) != pool.end())
        {
            if (pool[it.first].type() == typeid(VarPool))
            {
                return std::any_cast<VarPool &>(pool[it.first]).getBool(it.second);
            }
        }
        return std::nullopt;
    }

    if (!exists(name))
        return std::nullopt;

    try
    {

        std::reference_wrapper<bool> ref = std::any_cast<bool &>(pool[name]);

        return std::optional<std::reference_wrapper<bool>>{ref};
    }
    catch (const std::bad_any_cast &e)
    {
        return std::nullopt;
    }
}

std::optional<std::reference_wrapper<double>> VarPool::getDouble(const std::string &name)
{

    auto it = split_key(name);

    if (!it.second.empty())
    {
        if (pool.find(it.first) != pool.end())
        {
            if (pool[it.first].type() == typeid(VarPool))
            {
                return std::any_cast<VarPool &>(pool[it.first]).getDouble(it.second);
            }
        }
        return std::nullopt;
    }

    if (!exists(name))
        return std::nullopt;

    try
    {

        std::reference_wrapper<double> ref = std::any_cast<double &>(pool[name]);

        return std::optional<std::reference_wrapper<double>>{ref};
    }
    catch (const std::bad_any_cast &e)
    {
        return std::nullopt;
    }
}

std::optional<std::reference_wrapper<std::string>> VarPool::getString(const std::string &name)
{

    auto it = split_key(name);

    if (!it.second.empty())
    {
        if (pool.find(it.first) != pool.end())
        {
            if (pool[it.first].type() == typeid(VarPool))
            {
                return std::any_cast<VarPool &>(pool[it.first]).getString(it.second);
            }
        }
        return std::nullopt;
    }

    if (!exists(name))
        return std::nullopt;

    try
    {

        std::reference_wrapper<std::string> ref = std::any_cast<std::string &>(pool[name]);

        return std::optional<std::reference_wrapper<std::string>>{ref};
    }
    catch (const std::bad_any_cast &e)
    {
        return std::nullopt;
    }
}

std::optional<std::reference_wrapper<std::vector<int>>> VarPool::getIntList(const std::string &name)
{

    auto it = split_key(name);

    if (!it.second.empty())
    {
        if (pool.find(it.first) != pool.end())
        {
            if (pool[it.first].type() == typeid(VarPool))
            {
                return std::any_cast<VarPool &>(pool[it.first]).getIntList(it.second);
            }
        }
        return std::nullopt;
    }

    if (!exists(name))
        return std::nullopt;

    try
    {

        std::reference_wrapper<std::vector<int>> ref = std::any_cast<std::vector<int> &>(pool[name]);

        return std::optional<std::reference_wrapper<std::vector<int>>>{ref};
    }
    catch (const std::bad_any_cast &e)
    {
        return std::nullopt;
    }
}

std::optional<std::reference_wrapper<std::vector<double>>> VarPool::getDoubleList(const std::string &name)
{

    auto it = split_key(name);

    if (!it.second.empty())
    {
        if (pool.find(it.first) != pool.end())
        {
            if (pool[it.first].type() == typeid(VarPool))
            {
                return std::any_cast<VarPool &>(pool[it.first]).getDoubleList(it.second);
            }
        }
        return std::nullopt;
    }

    if (!exists(name))
        return std::nullopt;

    try
    {
        std::reference_wrapper<std::vector<double>> ref = std::any_cast<std::vector<double> &>(pool[name]);

        return std::optional<std::reference_wrapper<std::vector<double>>>{ref};
    }
    catch (const std::bad_any_cast &e)
    {
        return std::nullopt;
    }
}

std::optional<std::reference_wrapper<std::vector<std::string>>> VarPool::getStringList(const std::string &name)
{

    if (!exists(name))
        return std::nullopt;

    try
    {

        std::reference_wrapper<std::vector<std::string>> ref = std::any_cast<std::vector<std::string> &>(pool[name]);

        return std::optional<std::reference_wrapper<std::vector<std::string>>>{ref};
    }
    catch (const std::bad_any_cast &e)
    {
        return std::nullopt;
    }
};

void VarPool::removeVar(const std::string &name)
{
    auto it = split_key(name);

    if (!it.second.empty())
    {
        if (pool.find(it.first) != pool.end())
        {
            if (pool[it.first].type() == typeid(VarPool))
            {
                std::any_cast<VarPool &>(pool[it.first]).removeVar(it.second);
            }
        }
        return;
    }

    pool.erase(name);
}

std::optional<std::reference_wrapper<std::vector<VarPool>>> VarPool::getList(const std::string &name)
{

    auto it = split_key(name);

    if (!it.second.empty())
    {
        if (pool.find(it.first) != pool.end())
        {
            if (pool[it.first].type() == typeid(VarPool))
            {
                return std::any_cast<VarPool &>(pool[it.first]).getList(it.second);
            }
        }
        return std::nullopt;
    }

    if (!exists(name))
        return std::nullopt;

    try
    {

        std::reference_wrapper<std::vector<VarPool>> ref = std::any_cast<std::vector<VarPool> &>(pool[name]);

        return std::optional<std::reference_wrapper<std::vector<VarPool>>>{ref};
    }
    catch (const std::bad_any_cast &e)
    {
        return std::nullopt;
    }
}

void VarPool::setVar(const std::string &name, const std::any value)
{
    auto it = split_key(name);

    if (!it.second.empty())
    {
        if (pool.find(it.first) != pool.end())
        {
            if (pool[it.first].type() == typeid(VarPool))
            {
                std::any_cast<VarPool &>(pool[it.first]).setVar(it.second, value);
            }
        }
        return;
    }

    pool[name] = value;
}
