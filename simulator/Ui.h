#ifndef UI_H
#define UI_H

#include <vector>
#include <list>
#include <unordered_set>
#include <memory>
#include <cstdint>

namespace simulator
{
    class UiElement;
    class Ui;

    class UiElement
    {
    protected:
        uint32_t id_;
        std::shared_ptr<Ui> ui_;
    public:
        virtual void update(void)=0;
        virtual void draw(void)=0;

        void set_id(uint32_t id);
        uint32_t id(void);

        void associate_ui(std::shared_ptr<Ui> ui);
    };


    class Ui
    {
    private:
        typedef std::vector<std::vector<int8_t> > Buffer_;

        bool drawing_locked_;
        Buffer_ buffers_[2];
        bool current_back_buffer_;
        const static uint32_t DEFAULT_NUM_COLS_ = 30;
        const static uint32_t DEFAULT_NUM_ROWS_ = 30;

        uint32_t num_rows_;
        uint32_t num_cols_;

        std::list<std::shared_ptr<UiElement>> ui_elements_;
        std::unordered_set<uint32_t> ui_element_ids_;

        void init_(uint32_t num_rows, uint32_t num_cols);

        char printable_pixel_(int8_t pixel_value);

    public:
        Ui();
        Ui(uint32_t num_rows, uint32_t num_cols);

        uint32_t num_rows(void);
        uint32_t num_cols(void);

        void update_pixel(int32_t r, int32_t c, int8_t v);

        void render(void);
        void update(void);

        // void lock_drawing_(void);
        // void release_drawing_(void);

        void register_element(std::shared_ptr<UiElement> elm);
    };
};

#endif
