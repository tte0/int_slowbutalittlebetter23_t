#pragma once
#include <cstdlib>
#include <string>
#include <array>
#include <memory>
#include <iostream>
#include "int23_t.hpp"

/**
 * @brief Execute a qalc command-line expression and return its textual result.
 * This function invokes the external `qalc` CLI using a system call.
 * It passes the given expression to qalc with `--terse` flag,
 * reads the output from stdout, and returns the evaluated result as a string.
 * @param expr A valid mathematical expression understood by qalc.
 *             Example: "2 + 3 * 4"
 * @return The evaluated result of the expression, as a string.
 * @throws std::runtime_error if the qalc process cannot be opened.
 * @note This implementation starts a new process per call,
 *       so it is slow for repeated computations.
 *       Use the libqalc API directly for high-performance applications.
 */
std::string q_exec(const std::string& expr) {
    std::string cmd = "qalc --terse \"" + expr + "\"";
    std::array<char, 128> buffer{};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen failed");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        result += buffer.data();
    if (!result.empty() && result.back() == '\n') result.pop_back();
    return result;
}

bool q_equal(const int23_t::int23_t& a,const int23_t::int23_t& b){
    return q_exec(std::string(a)+" == "+std::string(b)) == "true";
}