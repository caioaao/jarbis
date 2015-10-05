#ifndef OPENGLUI_H
#define OPENGLUI_H

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "simulator/Ui.h"

namespace simulator
{
    class OpenglUi: public Ui
    {
    private:
        GLFWwindow * window_;
        static bool glfw_initialized_;
        static bool glew_initialized_;

        GLuint default_program_;

        void init_(void);
        static void glfw_err_callback_(int error, const char * desc);
        static GLuint create_program_(const std::string& vert_shader_path,
                                      const std::string& frag_shader_path);
        static GLuint create_shader_(const std::string& shader_path,
                                     GLenum shader_type);
        static std::string get_shader_src_(const std::string &filepath);

    public:
        OpenglUi();
        ~OpenglUi();
        virtual void render(void);
        virtual bool ui_exited(void);
        virtual std::shared_ptr<UiElement> create_polygon(
            std::vector<std::pair<int64_t, int64_t> > vertices,
            UiColor color);

        double normalize_xcoord(int64_t x_coord);
        double normalize_ycoord(int64_t y_coord);

        double normalize_rgb(uint8_t val);

        GLint uniform_color_location(void);
    };


    class OpenglUiPolygon: public UiElement
    {
    private:
        OpenglUi* ui_;
        UiColor color_;
        std::vector<std::pair<int64_t, int64_t>> vertices_;
        GLuint vao_id_;
        GLuint vbo_id_;
        std::vector<GLfloat> vertices_gl_;

    public:
        OpenglUiPolygon(
            OpenglUi *ui,
            std::vector<std::pair<int64_t, int64_t> > vertices,
            UiColor color);
        virtual void draw(void);
    };
};

#endif
