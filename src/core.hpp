
#ifndef FILESYSTEMSIMULATOR_CORE_HPP
#define FILESYSTEMSIMULATOR_CORE_HPP

#include <iostream>
#include <string>
const int DISK_SIZE = 100;
const int FILE_SIZE = 504;
const int DIR_SIZE = 31;
static int openBlock = -1;
static int openMode = -1;  // 0 = input, 1 = output, 2 = update
static int cursor = -1;

namespace fs {
/**
 * Last call for variadic fml::log.
 *
 * @tparam outStream - Output stream type.
 * @param os - Output stream.
 */
template <typename outStream>
void log(outStream& os) {
  // does nothing here
}

/**
 * Logs the output.
 *
 * @tparam outStream - Output stream type.
 * @tparam outType - Output type.
 * @tparam Ts - Variadic templates.
 * @param os - Output Stream.
 * @param output - Output.
 * @param args - Variadic parameters.
 */
template <typename outStream, typename outType, typename... Ts>
void log(outStream& os, const outType& output, const Ts... args) {
  os << output;
  log(os, args...);
}

}  // namespace fs

#endif  // FILESYSTEMSIMULATOR_CORE_HPP
