#include "simulator/Ui.h"

#include <iostream>
#include <algorithm>
#include <SDL/SDL.h>


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


    SdlUi::SdlUi()
    {
        init_();
    }


    void
    SdlUi::render(void)
    {
        //stub
    }


    void
    SdlUi::init_(void)
    {

    }
};
