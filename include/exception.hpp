#ifndef COSMODON_EXCEPTION
#define COSMODON_EXCEPTION

#include <string>

namespace cosmodon
{
    namespace exception
    {
        /**
         * A generic exception.
         *
         * More informative exceptions should be favored.
         */
        class base : public std::exception
        {
        protected:
            std::string m_message;

        public:
            /**
             * Constructor.
             */
            base(std::string message);

            /**
             * Destructor.
             */
            ~base() noexcept(true);

            /**
             * Retrieve stored message.
             */
            virtual const char* what() const noexcept(true);
        };

        /**
         * An exception caused by functionality so important, the program must stop.
         *
         * Only use when recovery is futile.
         */
        class fatal : public base
        {
        public:
            fatal(std::string message);
        };

        /**
         * A recoverable, almost somewhat anticipated, error.
         *
         * Use when the program is hindered, but the error is recoverable.
         */
        class error : public base
        {
        public:
            error(std::string message);
        };
    }
}

#endif
