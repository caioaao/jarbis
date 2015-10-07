#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

#include <base/Logger.h>

namespace base {
    class Exception {
    private:
        std::string desc_;
    public:
        Exception(){}
        void set_desc(const std::string& desc){ desc_ = desc; }
        std::string desc(void){ return desc_; }
    };


    template<typename T>
    T exception(std::string desc) {
        T ex;
        static_cast<Exception>(ex).set_desc(desc);

        corelog() << log_level(LOG_INFO)
                  << "Exception thrown. Description: " << desc << '\n';

        return ex;
    }
}


#endif
