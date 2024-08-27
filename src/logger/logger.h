#ifndef SECOND_TAKE_LOGGER
#define SECOND_TAKE_LOGGER

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "loggingdestinations.h"
#include "loglevels.h"
#include "timeproviders.h"
#include "visibility.h"

namespace second_take {

class DLL_PUBLIC Logger {
 public:
  virtual ~Logger();
  static Logger &getInstance();
  static Logger *getInstanceAsPointer();
  friend bool operator==(const Logger &lhs, const Logger &rhs);
  void trace(const std::string &message);
  void debug(const std::string &message);
  void info(const std::string &message);
  void warn(const std::string &message);
  void error(const std::string &message);
  void fatal(const std::string &message);
  void removeAllDestinations();
  std::size_t getCountOfLoggingDestinations();
  void addLoggingDestination(std::unique_ptr<LoggingDestination> destination);

 private:
  Logger();
  std::unique_ptr<TimeProvider> timeProvider;
  std::vector<std::unique_ptr<LoggingDestination>> loggingDestinations;

  void doLogging(const LogLevel &logLevel, const std::string &message);
};

}  // namespace second_take

#endif  // SECOND_TAKE_LOGGER