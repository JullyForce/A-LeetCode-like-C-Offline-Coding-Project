//
//  TestExecutor.hpp
//  Algorithms
//
//  Created by J.C. on 6/12/24.
//

#ifndef TestExecutor_h
#define TestExecutor_h

#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <utility>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

// Base case function for template recursion
template <std::size_t Index, typename Ret, typename... Args>
void processArgument(const std::function<Ret(Args...)>& func, const std::vector<json>& jsonArgs, std::tuple<Args...>& args) {
    using ArgType = typename std::tuple_element<Index, std::tuple<Args...>>::type;
    
    // Special handling for char and std::vector<char>
    if constexpr (std::is_same_v<ArgType, char>) {
        std::string temp = jsonArgs[Index].get<std::string>();
        std::get<Index>(args) = temp[0];
        std::transform(temp.begin(), temp.end(), std::get<Index>(args).begin(), [] (const std::string & s) { return s[0]; });
    } else if constexpr (std::is_same_v<ArgType, std::vector<char>>) {
        std::vector<std::string> temp = jsonArgs[Index].get<std::vector<std::string>>();
        std::get<Index>(args) = std::vector<char>(temp.size());
        std::transform(temp.begin(), temp.end(), std::get<Index>(args).begin(), [] (const std::string & s) { return s[0]; });
    } else if constexpr (std::is_same_v<ArgType, std::vector<std::vector<char>>>) {
        std::vector<std::vector<std::string>> temp = jsonArgs[Index].get<std::vector<std::vector<std::string>>>();
        std::get<Index>(args) = std::vector<std::vector<char>>(temp.size(), std::vector<char>(temp[0].size()));
        std::transform(temp.begin(), temp.end(), std::get<Index>(args).begin(),
                       [] (const std::vector<std::string> & v) {
            std::vector<char> ans(v.size());
            std::transform(v.begin(), v.end(), ans.begin(), [] (const std::string & s) { return s[0]; });
            return ans;
        });
    } else {
        std::get<Index>(args) = jsonArgs[Index].get<ArgType>();
    }
//    std::get<Index>(args) = jsonArgs[Index].get<typename std::tuple_element<Index, std::tuple<Args...>>::type>();
}

// Recursive function to process each argument
template <std::size_t Index = 0, typename Ret, typename... Args>
typename std::enable_if<Index == sizeof...(Args), Ret>::type
    processArguments(const std::function<Ret(Args...)>& func, const std::vector<json>& jsonArgs, std::tuple<Args...>& args) {
    return std::apply(func, args);
}

template <std::size_t Index = 0, typename Ret, typename... Args>
typename std::enable_if<Index < sizeof...(Args), Ret>::type
    processArguments(const std::function<Ret(Args...)>& func, const std::vector<json>& jsonArgs, std::tuple<Args...>& args) {
    processArgument<Index>(func, jsonArgs, args);
    return processArguments<Index + 1, Ret, Args...>(func, jsonArgs, args);
}

template<typename Ret, typename... Args>
int ExecuteTest(const std::function<Ret(Args...)>& testFcn, const std::string& filePath) {
    std::string wd("/Users/junchen/Documents/Xcode/Algorithms/Algorithms/Algorithms/");
    std::ifstream inputFile(wd + filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return 1;
    }
    
    std::string line;
    std::vector<json> argsVec;
    while (std::getline(inputFile, line)) {
        json jsonData;
        try {
            jsonData = json::parse(line);
        } catch (const json::exception& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            continue;
        }
        
        argsVec.push_back(jsonData);
    }
    if (argsVec.size() % sizeof...(Args) != 0) {
        std::cerr << "Invalid number of arguments in JSON" << std::endl;
    }
    
    std::string outFilePath(filePath + ".out");
    std::ofstream outputFile(wd + outFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << outFilePath << std::endl;
        return 1;
    }

    while (!argsVec.empty()) {
        // We may be providing a long-than-needed argsVec to processArguments, who will only take the first N, and leave the rest for later runs
        std::tuple<Args...> args;
        json jResult = processArguments(testFcn, argsVec, args);
        
        //    std::vector<typename std::common_type<Args...>::type> args;
        //    try {
        //        args.reserve(sizeof...(Args));
        //        (void)std::initializer_list<int>{(args.push_back(argsVec[std::to_string(args.size())].get<Args>()), 0)...};
        //    } catch (const json::exception& e) {
        //        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        //        return 1;
        //    }
        //
        //    json jResult = std::apply(testFcn, args);
        
        outputFile << jResult.dump() << std::endl;
#ifndef NDEBUG
        std::cout << jResult.dump() << std::endl;
#endif
        
        // Remove the first N used arguments from argsVec (and repeat invoking if more left)
        std::vector<json>(argsVec.begin()+sizeof...(Args), argsVec.end()).swap(argsVec);
    }
    
    outputFile.close();
    std::cout << "Test result has been written to: " << outFilePath << std::endl;
    
    return 0;
}

// Utility function to create lambda from member function and instance
//template <typename R, typename C, typename... Args>
//auto createLambda(R (C::*method)(Args...), C* instance) -> std::function<R(typename std::decay<Args>::type...)> {
//    return [instance, method](typename std::decay<Args>::type... args) -> R {
//        return (instance->*method)(std::forward<Args>(args)...);
//    };
//}
template <typename R, typename C, typename... Args>
std::function<R (typename std::remove_reference<Args>::type...)> createLambda(R (C::*method)(Args...), C* instance) {
    return [instance, method](typename std::remove_reference<Args>::type... args) -> R {
        return (instance->*method)(args...);
    };
}


///------------------------------- MACROS ---------------------------------///

//#define TEST_PROBLEM(NO)                                                    \
//                                                                            \
//using namespace LC##NO;                                                     \
//                                                                            \
//Solution sol;                                                               \
//auto testWrapper = createLambda(Solution::testEntry, &sol);                 \
//return ExecuteTest(testWrapper, "Resources/LC"  #NO  ".txt");               \


// With numbered Leetcode problems, we can conveniently name each problem in
// a LC1234-like fashion, and use the same name for the header file containing
// the problem solution and the test case.
// To-use:
//     1. place the problem solution in a header file named LC1234.hpp, in
//        LeetCode folder, and the test case in a Resources folder with the
//        same name as the header file, with a .txt extension.
//     2. in the solution class, define a public static function stub
//        "testEntry", pointing to the public test function solving the problem
//     3. include the header file for that specific problem in ProblemSet.hpp
//     4. in main(), use the TEST_PROBLEM macro to run the test case

#define TEST_PROBLEM(NO)                                                    \
                                                                            \
{                                                                           \
LC##NO::Solution sol;                                                       \
auto testWrapper = createLambda(LC##NO::Solution::testEntry, &sol);         \
(void) ExecuteTest(testWrapper, "./Resources/LC"  #NO  ".txt");             \
}

// This MACRO serves the same purpose as TEST_PROBLEM, but for generic problems
// (i.e. not LeetCode problems). The only difference is that the header file
// containing the solution class is prefixed with "GP_" instead of "LC", and
// natural naming of each problems is preferred.
#define TEST_GENERIC(TITLE)                                                 \
                                                                            \
{                                                                           \
GP_##TITLE::Solution sol;                                                   \
auto testWrapper = createLambda(GP_##TITLE::Solution::testEntry, &sol);     \
(void) ExecuteTest(testWrapper, "./Resources/GP_"  #TITLE  ".txt");         \
}

// Swiss gear one-for-everything MACRO
#define RUNTEST(TEST_ID)                                                    \
                                                                            \
{                                                                           \
TEST_ID::Solution sol;                                                      \
auto testWrapper = createLambda(TEST_ID::Solution::testEntry, &sol);        \
(void) ExecuteTest(testWrapper, "./Resources/"  #TEST_ID  ".txt");          \
}


#endif /* TestExecutor_h */
