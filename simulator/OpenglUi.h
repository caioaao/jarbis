#ifndef OPENGLUI_H
#define OPENGLUI_H

#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "base/LinAlg.h"

#include "simulator/Ui.h"

namespace simulator {
    class OpenglUi: public Ui {
    private:
        GLFWwindow * window_;
        static bool glfw_initialized_;
        static bool glew_initialized_;

        GLuint default_program_;

        base::Matrix<float, 3, 3> scale_transform_;

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
            const std::vector<base::Matrix<float, 2, 1> >& vertices,
            UiColor color);

        float normalize_xcoord(int64_t x_coord);
        float normalize_ycoord(int64_t y_coord);

        float normalize_rgb(uint8_t val);

        GLint uniform_color_location(void);
        GLint uniform_transform_location(void);

        base::Matrix<float, 3, 3> scale_transform(void);
    };


    class OpenglUiPolygon: public UiElement {
    private:
        OpenglUi* ui_;
        UiColor color_;
        GLuint vao_id_;
        GLuint vbo_id_;
        std::vector<GLfloat> vertices_gl_;
        base::Matrix<float, 3, 3> transform_;

    public:
        OpenglUiPolygon(
            OpenglUi *ui,
            const std::vector<base::Matrix<float, 2, 1> >& vertices,
            UiColor color);
        virtual void draw(void);
    };
}

#endif
