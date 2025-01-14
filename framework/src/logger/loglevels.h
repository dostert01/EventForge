#ifndef LOG_LEVELS_H
#define LOG_LEVELS_H

#include <map>
#include <string>
#include <optional>

using namespace std;
namespace event_forge {

#define LOG_PREFIX_TRACE "TRACE"
#define LOG_PREFIX_DEBUG "DEBUG"
#define LOG_PREFIX_INFO "INFO"
#define LOG_PREFIX_WARN "WARN"
#define LOG_PREFIX_ERROR "ERROR"
#define LOG_PREFIX_FATAL "FATAL"
#define LOG_PREFIX_NO_LOGGING "NO_LOGGING"

#define MAX_LOG_LEVEL_ENV_VAR_NAME "SECOND_TAKE_MAX_LOG_LEVEL"

enum class LogLevel {
  LOG_LEVEL_TRACE = 6,
  LOG_LEVEL_DEBUG = 5,
  LOG_LEVEL_INFO = 4,
  LOG_LEVEL_WARN = 3,
  LOG_LEVEL_ERROR = 2,
  LOG_LEVEL_FATAL = 1,
  LOG_LEVEL_NO_LOGGING = 0
};

class LogLevelStringMapper {
 public:
  LogLevelStringMapper();
  optional<LogLevel> string2LogLevel(const string &levelString) const;
  optional<string> logLevel2String(const LogLevel &logLevel) const ;

 private:
  map<LogLevel, string> logLevels;
};

}  // namespace event_forge

#endif  // LOG_LEVELS_H