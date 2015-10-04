#include "simulator/Ui.h"

#include "base/Logger.h"


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
    UiElement::set_ui(std::shared_ptr<Ui> ui)
    {
        ui_ = ui;
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
            base::corelog() << base::log_level(base::LOG_ERR)
                            << "Element " << elm->id() << " already exists\n";
        }
    }


    uint8_t UiColor::r(void)
    {
        return r_;
    }


    uint8_t UiColor::g(void)
    {
        return g_;
    }


    uint8_t UiColor::b(void)
    {
        return b_;
    }


    uint8_t UiColor::set_r(uint8_t r)
    {
        r_ = r;
    }


    uint8_t UiColor::set_g(uint8_t g)
    {
        g_ = g;
    }


    uint8_t UiColor::set_b(uint8_t b)
    {
        b_ = b;
    }
};
