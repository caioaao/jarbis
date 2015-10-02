#include "simulator/Ui.h"

#include <iostream>
#include <algorithm>



namespace simulator
{

    void
    UiElement::set_id(uint32_t id)
    {
        id_ = id;
    }


    uint32_t
    UiElement::id(void)
    {
        return id_;
    }


    void
    UiElement::associate_ui(std::shared_ptr<Ui> ui)
    {
        ui_ = ui;
    }


    Ui::Ui()
    {
        init_(DEFAULT_NUM_ROWS_, DEFAULT_NUM_COLS_);
    }


    Ui::Ui(uint32_t num_rows, uint32_t num_cols)
    {
        init_(num_rows, num_cols);
    }


    void
    Ui::init_(uint32_t num_rows, uint32_t num_cols)
    {
        for(int i = 0; i < 2; ++i)
        {
            buffers_[i].assign(num_rows, std::vector<int8_t>(num_cols, 0));
        }

        current_back_buffer_ = 0;
    }


    char
    Ui::printable_pixel_(int8_t pixel_value)
    {
        char char_value;
        if(0 == pixel_value) char_value = ' ';
        else char_value = '#';

        return char_value;
    }


    uint32_t
    Ui::num_rows(void)
    {
        return buffers_[0].size();
    }


    uint32_t
    Ui::num_cols(void)
    {
        return buffers_[0][0].size();
    }

    void
    Ui::update_pixel(int32_t r, int32_t c, int8_t v)
    {
        if(r >= 0 && c >= 0
           && r < (int32_t)buffers_[current_back_buffer_].size()
           && c < (int32_t)buffers_[current_back_buffer_][r].size())
        {
            buffers_[current_back_buffer_][r][c] = v;
        }
    }


    void
    Ui::render(void)
    {
        current_back_buffer_ = !current_back_buffer_;
        buffers_[current_back_buffer_] = buffers_[!current_back_buffer_];

        Buffer_ &buffer_to_be_printed = buffers_[!current_back_buffer_];

        for(int32_t i = 0; i < (int32_t)buffer_to_be_printed.size(); ++i)
        {
            for(int32_t j = 0; j < (int32_t)buffer_to_be_printed[i].size(); ++j)
            {
                std::cout << printable_pixel_(buffer_to_be_printed[i][j]);
            }
            std::cout << std::endl;
        }
    }


    void
    Ui::update(void)
    {
        for(std::shared_ptr<UiElement> &elm : ui_elements_)
        {
            elm->update();
        }
        for(std::shared_ptr<UiElement> &elm : ui_elements_)
        {
            elm->draw();
        }
    }


    void
    Ui::register_element(std::shared_ptr<UiElement> elm)
    {
        if(ui_element_ids_.count(elm->id()) == 0)
        {
            ui_element_ids_.insert(elm->id());
            ui_elements_.push_front(elm);
        }
        else
        {
            std::cerr << "Element " << elm->id() << " already exists"
                      << std::endl;
        }
    }

};
