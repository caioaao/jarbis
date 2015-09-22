#ifndef UI_H
#define UI_H

#include <string>
#include <vector>

namespace simulator
{
    class Ui
    {
    private:
        typedef std::vector<std::vector<int> > Buffer_;
        bool drawing_locked_;
        Buffer_ buffers_[2];
        unsigned int current_back_buffer_;
        const static unsigned int DEFAULT_NUM_COLS_ = 30;
        const static unsigned int DEFAULT_NUM_ROWS_ = 30;

        unsigned int num_rows_;
        unsigned int num_cols_;

        void init_(unsigned int num_rows, unsigned int num_cols);

        char printable_pixel_(int pixel_value);

    public:
        Ui();
        Ui(unsigned int num_rows, unsigned int num_cols);

        unsigned int num_rows(void);
        unsigned int num_cols(void);

        void update_pixel(unsigned int r, unsigned int c, int v);

        void render(void);

        void lock_drawing_(void);
        void release_drawing_(void);
    };
};

#endif
