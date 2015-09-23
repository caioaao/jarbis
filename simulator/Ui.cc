#include <iostream>
#include <algorithm>

#include "simulator/Ui.h"

namespace simulator
{

    void
    UiElement::set_id(unsigned int id)
    {
        id_ = id;
    }


    unsigned int
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


    Ui::Ui(unsigned int num_rows, unsigned int num_cols)
    {
        init_(num_rows, num_cols);
    }


    void
    Ui::init_(unsigned int num_rows, unsigned int num_cols)
    {
        for(int i = 0; i < 2; ++i)
        {
            buffers_[i].assign(num_rows, std::vector<int>(num_cols, 0));
        }

        current_back_buffer_ = 0;
    }


    char
    Ui::printable_pixel_(int pixel_value)
    {
        char char_value;
        if(0 == pixel_value) char_value = ' ';
        else char_value = '#';

        return char_value;
    }


    unsigned int
    Ui::num_rows(void)
    {
        return buffers_[0].size();
    }


    unsigned int
    Ui::num_cols(void)
    {
        return buffers_[0][0].size();
    }

    void
    Ui::update_pixel(unsigned int r, unsigned int c, int v)
    {
        buffers_[current_back_buffer_][r][c] = v;
    }


    void
    Ui::render(void)
    {
        current_back_buffer_ = !current_back_buffer_;
        buffers_[current_back_buffer_] = buffers_[!current_back_buffer_];

        Buffer_ &buffer_to_be_printed = buffers_[!current_back_buffer_];

        for(int i = 0; i < (int)buffer_to_be_printed.size(); ++i)
        {
            std::cout << std::endl;
        }

        for(int i = 0; i < (int)buffer_to_be_printed.size(); ++i)
        {
            for(int j = 0; j < (int)buffer_to_be_printed[i].size(); ++j)
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


    // void
    // Ui::lock_drawing_(void)
    // {
    //     while(drawing_locked_);
    //     drawing_locked_ = true;
    // }
    //
    // void
    // Ui::release_drawing_(void)
    // {
    //     drawing_locked_ = false;
    // }

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
