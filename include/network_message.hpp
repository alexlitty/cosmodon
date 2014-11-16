#ifndef COSMODON_NETWORK_MESSAGE
#define COSMODON_NETWORK_MESSAGE

#include <vector>
#include <network_frame.hpp>

namespace cosmodon
{
    namespace network
    {
        /**
         * A message of data, composed of frames.
         *
         * Messages are designed to be strict and purely constructive: You may add frames, but you
         * may not sort or delete particular frames. Add frames in the order you would like them
         * received.
         *
         * When adding frames, you shall be passing frame pointers. Allow the message to delete
         * the frame upon destructed.
         *
         * Each frame is composed of its individual parts, preceded by a single header part,
         * which indicates the format of the frame.
         */
        class message
        {
        protected:
            // Collection of frames, composing this message.
            std::vector<frame::base*> m_frames;

            // Indicators if we have already retrieved the current frame's header part.
            bool m_frame_header;

            // Internal frame counter, for counting parts in and out of them.
            unsigned char m_current_frame;

        public:
            /**
             * Constructor.
             */
            message();

            /**
             * Destructor.
             *
             * Free the frame pointers.
             */
            ~message();

            /**
             * Reset internal frame counter.
             */
            void reset();

            /**
             * Add a frame.
             *
             * This message assumes responsibility of freeing the given pointer.
             */
            void add(frame::base *new_frame);

            /**
             * Check whether there are more parts to input or output.
             */
            bool more();

            /**
             * Retrieve the next frame.
             */
            void get_next_part(const void *data, size_t length);
        };
    }
}

#endif
