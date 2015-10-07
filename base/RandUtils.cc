#include "base/RandUtils.h"

#include <random>

namespace base
{
    std::default_random_engine generator_;

    std::string ALPHABET_ALPHANUMERIC =
        "QWERTYUIOPASDFGHJKLZXCVBNM"
        "qwertyuiopasdfghjklzxcvbnm"
        "1234567890";

    std::string
    random_string(size_t len, const std::string& alphabet)
    {
        std::uniform_int_distribution<size_t> distribution(0,
                                                           alphabet.size() - 1);

        std::string s(len, '\0');

        for(std::string::iterator it = s.begin(); it != s.end(); ++it)
        {
            (*it) = alphabet[distribution(generator_) % alphabet.size()];
        }

        return s;
    }
}
