#include "base/Logger.h"

#include <iostream>

#include "base/Config.h"

namespace base {
    LogStream&
    corelog(void) {
        static LogStream *ls = new LogStream();

        return *ls;
    }


    LogStream::LogStream():
        out_(std::cout) {
        init_();
    }


    void
    LogStream::init_() {
        const ConfigMap& syscfg = SysConfig::instance();
        printable_log_level_ = static_cast<LogLevel>(
            syscfg.get("default_loglevel"));
        log_level_ = LogLevel::LOG_INFO;
    }


    LogLevel
    LogStream::log_level(void) {
        return log_level_;
    }


    LogLevel
    LogStream::printable_log_level(void) {
        return printable_log_level_;
    }


    void
    LogStream::set_log_level(LogLevel new_level) {
        log_level_ = new_level;
    }


    void
    LogStream::set_printable_log_level(LogLevel new_level) {
        printable_log_level_ = new_level;
    }


    LogStream const&
    LogStream::operator<<(std::ostream &(*F)(std::ostream&)) const {
        F(out_);
        return *this;
    }


    LogStream&
    set_log_level_(LogStream &stream, LogLevel lv) {
        stream.set_log_level(lv);
        return stream;
    }


    LogStreamManip<LogLevel>
    log_level(LogLevel lv) {
        return LogStreamManip<LogLevel>(set_log_level_, lv);
    }
}
