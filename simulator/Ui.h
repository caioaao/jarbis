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
    protected:
        std::list<std::shared_ptr<UiElement>> ui_elements_;
        std::unordered_set<uint32_t> ui_element_ids_;

    public:
        virtual void render(void)=0;
        void update(void);

        // void lock_drawing_(void);
        // void release_drawing_(void);

        void register_element(std::shared_ptr<UiElement> elm);
    };


    class SdlUi: public Ui
    {
    private:
        void init_(void);
    public:
        SdlUi();
        virtual void render(void);
    };
};

#endif
