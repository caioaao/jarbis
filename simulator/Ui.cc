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
    Ui::register_element(std::shared_ptr<UiElement> elm)
    {
        base::corelog() << base::log_level(base::LOG_INFO)
                        << "Registering element\n";
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

        base::corelog() << base::log_level(base::LOG_INFO)
                        << "Registered element\n";
    }


    void
    Ui::draw_elements_(void)
    {
        for(std::shared_ptr<UiElement>& elm : ui_elements_)
        {
            elm->draw();
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


    void UiColor::set_r(uint8_t r)
    {
        r_ = r;
    }


    void UiColor::set_g(uint8_t g)
    {
        g_ = g;
    }


    void UiColor::set_b(uint8_t b)
    {
        b_ = b;
    }
};
