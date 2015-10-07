#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <iomanip>

namespace base {
    enum LogLevel {
        LOG_INFO,
        LOG_DEBUG,
        LOG_CRIT,
        LOG_ERR,
        LOG_NONE
    };


    class LogStream;

    template <typename T>
    class LogStreamManip {
        typedef LogStream& (*LogStreamManipAction_)(LogStream&, T);
    public:
        LogStreamManip(LogStreamManipAction_ action, T val) :action_(action), val_(val){}
        LogStream& act(LogStream& l) { return action_(l,val_); }
    private:
        LogStreamManipAction_ action_;
        T val_;

    };

    class LogStream {
    private:
        std::ostream &out_;
        LogLevel log_level_;
        LogLevel printable_log_level_;

        void init_();
    public:
        LogStream();

        LogLevel log_level(void);
        LogLevel printable_log_level(void);

        void set_log_level(LogLevel new_level);
        void set_printable_log_level(LogLevel new_level);

        template <typename T>
        LogStream& operator<<(LogStreamManip<T> manip) {
                return manip.act(*this);
            }

        LogStream const& operator<<(std::ostream &(*F)(std::ostream&)) const;

        template <typename T>
        LogStream const& operator<<(T const& v) const {
                if(log_level_ >= printable_log_level_) {
                    out_<< v;
                }

                return *this;
            }
    };


    LogStreamManip<LogLevel> log_level(LogLevel lv);

    LogStream& corelog(void);
}

#endif
