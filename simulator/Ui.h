#ifndef UI_H
#define UI_H

#include <vector>
#include <list>
#include <unordered_set>
#include <memory>

namespace simulator
{
    class UiElement;
    class Ui;

    class UiElement
    {
    private:
        unsigned int id_;
        std::shared_ptr<Ui> ui_;
    public:
        virtual void update(void)=0;
        virtual void draw(void)=0;

        void set_id(unsigned int id);
        unsigned int id(void);

        void associate_ui(std::shared_ptr<Ui> ui);
    };


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

        std::list<std::shared_ptr<UiElement>> ui_elements_;
        std::unordered_set<unsigned int> ui_element_ids_;

        void init_(unsigned int num_rows, unsigned int num_cols);

        char printable_pixel_(int pixel_value);

    public:
        Ui();
        Ui(unsigned int num_rows, unsigned int num_cols);

        unsigned int num_rows(void);
        unsigned int num_cols(void);

        void update_pixel(unsigned int r, unsigned int c, int v);

        void render(void);
        void update(void);

        // void lock_drawing_(void);
        // void release_drawing_(void);

        void register_element(std::shared_ptr<UiElement> elm);
    };
};

#endif
