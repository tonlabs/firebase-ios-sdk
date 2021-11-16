/*
 * Copyright 2017 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Firestore/core/src/util/log.h"

#include <atomic>
#include <cctype>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <ios>
#include <iostream>
#include <mutex>
#include <string>

#include "Firestore/core/src/util/hard_assert.h"
#include "grpc/support/log.h"

namespace firebase {
namespace firestore {
namespace util {
namespace {

std::mutex* gLogMutex = new std::mutex();

std::atomic<LogLevel> g_log_level(kLogLevelNotice);

bool g_grpc_log_function_installed = false;

LogLevel LogLevelFromGrpcSeverity(gpr_log_severity severity) {
  switch (severity) {
    case GPR_LOG_SEVERITY_DEBUG:
      return kLogLevelDebug;
    case GPR_LOG_SEVERITY_INFO:
      return kLogLevelNotice;
    case GPR_LOG_SEVERITY_ERROR:
      return kLogLevelError;
    default:
      std::cerr << "INTERNAL ERROR: Unknown gpr_log_severity: " << static_cast<int>(severity) << std::endl;
      UNREACHABLE();
      break;
  }
}

gpr_log_severity GrpcSeverityFromLogLevel(LogLevel log_level) {
  switch (log_level) {
    case kLogLevelDebug:
      return GPR_LOG_SEVERITY_DEBUG;
    case kLogLevelNotice:
      return GPR_LOG_SEVERITY_INFO;
    case kLogLevelError:
    case kLogLevelWarning:
      return GPR_LOG_SEVERITY_ERROR;
    default:
      std::cerr << "INTERNAL ERROR: Unknown LogLevel: " << static_cast<int>(log_level) << std::endl;
      UNREACHABLE();
      break;
  }
}

void GrpcLogFunction(gpr_log_func_args* args) {
  LogLevel log_level = LogLevelFromGrpcSeverity(args->severity);
  std::string message = std::string("<GRPC> ") + args->message;
  LogMessage(log_level, message);
}

}  // namespace

void LogSetLevel(LogLevel level) {
  g_log_level = level;
  gpr_set_log_verbosity(GrpcSeverityFromLogLevel(level));
}

bool LogIsLoggable(LogLevel level) {
  return level >= g_log_level;
}

void LogMessage(LogLevel log_level, const std::string& message) {
  if (log_level < g_log_level) {
    return;
  }

  const char* level_word;

  switch (log_level) {
    case kLogLevelDebug:
      level_word = "DEBUG";
      break;
    case kLogLevelWarning:
      level_word = "WARNING";
      break;
    case kLogLevelError:
      level_word = "ERROR";
      break;
    case kLogLevelNotice:
      level_word = "INFO";
      break;
    default:
      std::cerr << "INTERNAL ERROR: Unknown log_level: " << static_cast<int>(log_level) << std::endl;
      UNREACHABLE();
      break;
  }

  std::lock_guard<std::mutex> lock(*gLogMutex);

  if (! g_grpc_log_function_installed) {
    g_grpc_log_function_installed = true;
    gpr_set_log_function(GrpcLogFunction);
    gpr_set_log_verbosity(GrpcSeverityFromLogLevel(g_log_level));
  }

  std::cout << ">iOS< " << UnityIssue1154TestAppIos::FormattedTimestamp() << " -- " << level_word << ": " << message << std::endl;
}

}  // namespace util
}  // namespace firestore
}  // namespace firebase

namespace UnityIssue1154TestAppIos {

std::string FormattedTimestamp() {
  auto timestamp = std::chrono::system_clock::now();
  std::time_t ctime_timestamp = std::chrono::system_clock::to_time_t(timestamp);
  std::string formatted_timestamp(std::ctime(&ctime_timestamp));
  while (formatted_timestamp.size() > 0) {
    auto last_char = formatted_timestamp[formatted_timestamp.size() - 1];
    if (!std::isspace(last_char)) {
      break;
    }
    formatted_timestamp.pop_back();
  }
  return formatted_timestamp;
}

std::string FormattedElapsedTime(std::chrono::time_point<std::chrono::steady_clock> start) {
  std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;

  std::ostringstream ss;
  ss << std::fixed;
  ss << std::setprecision(2);
  ss << elapsed_seconds.count() << "s";
  return ss.str();
}

}  // namespace UnityIssue1154TestAppIos
