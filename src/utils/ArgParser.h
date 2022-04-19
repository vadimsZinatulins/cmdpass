#pragma once

#include <set>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

namespace cmdpass
{

namespace utils
{

/**
 * @brief Simple command line argument parser 
 * 
 */
class ArgParser
{
public:
    ArgParser(int argc, char *argv[]);
    ArgParser(std::string argv);
    ~ArgParser();

    /**
     * @brief Adds an action to execute whenever an argument is found.
     * 
     * @param params Set of arguments to search for. These arguments represent the same action.
     * @param action The corresponding action for the parameter.
     */
    void add(std::set<std::string> params, std::function<void()> action);

    /**
     * @brief Adds an action to execute whenever an argument is found. A value for the argument is required.
     * 
     * @param params Set of arguments to search for. These arguments represent the same action.
     * @param action The corresponding action for the parameter with an value.
     */
    void add(std::set<std::string> params, std::function<void(std::string)> action);

    /**
     * @brief Parses the arguments 
     */
    void parse();
private:
    std::vector<std::string> m_arguments;
    std::unordered_map<std::string, std::function<void(std::vector<std::string> &, std::size_t &)>> m_actions;
};

}

}
