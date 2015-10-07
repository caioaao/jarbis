#ifndef UI_H
#define UI_H

#include <vector>
#include <list>
#include <unordered_set>
#include <memory>
#include <string>
#include <utility>

#include <cstdint>

#include "base/Exception.h"

namespace simulator
{
    const size_t MAIN_WINDOW_WIDTH = 1024;
    const size_t MAIN_WINDOW_HEIGHT = 1024;

    class Ui;
    class UiElement;
    class UiColor;

    class UiElement
    {
    protected:
        uint32_t id_;

    public:
        virtual void draw(void)=0;

        void set_id(uint32_t id);
        uint32_t id(void);
    };


    class Ui
    {
    protected:
        std::list<std::shared_ptr<UiElement>> ui_elements_;
        std::unordered_set<uint32_t> ui_element_ids_;

    public:
        virtual void render(void)=0;
        virtual bool ui_exited(void)=0;
        virtual std::shared_ptr<UiElement> create_polygon(
            std::vector<std::pair<int64_t, int64_t> > vertices,
            UiColor color)=0;
        void draw_elements_(void);
//         virtual shared_ptr<UiElement> create_dot(
//             std::pair<int64_t, int64_t> position,
//             UiColor color)=0;


        // void lock_drawing_(void);
        // void release_drawing_(void);

        void register_element(std::shared_ptr<UiElement> elm);
    };


    class UiColor
    {
    private:
        uint8_t r_, g_, b_;
    public:
        UiColor(uint8_t r, uint8_t g, uint8_t b)
            :r_(r), g_(g), b_(b) { }

        uint8_t r(void);
        uint8_t g(void);
        uint8_t b(void);

        void set_r(uint8_t r);
        void set_g(uint8_t g);
        void set_b(uint8_t b);
    };

    class UiException: public base::Exception {};


    class UiInitException: public UiException {};
}

#endif
