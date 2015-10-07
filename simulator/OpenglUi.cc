#include "OpenglUi.h"

#include <fstream>
#include <sstream>
#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "base/Config.h"
#include "base/Logger.h"
#include "base/debug.h"

#include "simulator/Ui.h"

namespace simulator {
    OpenglUi::OpenglUi() {
        init_();
    }


    OpenglUi::~OpenglUi() {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }


    void
    OpenglUi::init_(void) {
        glfwSetErrorCallback(glfw_err_callback_);

        if(!glfwInit()) {
            throw base::exception<UiInitException>("GLFW failed to initialize");
        }

        // Config to use GLSL newer version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


        window_ = glfwCreateWindow(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT,
                                   "Simulator", nullptr, nullptr);

        if(nullptr == window_) {
            throw base::exception<UiInitException>("Failed to create window");
        }

        glfwMakeContextCurrent(window_);
        glfwSwapInterval(1);

        glewExperimental = true;
        if(GLEW_OK != glewInit()) {
            throw base::exception<UiInitException>("GLEW failed to initialize");
        }

        default_program_ = create_program_("vert.glsl",
                                           "frag.glsl");
        glUseProgram(default_program_);

        // background is white
        glClearColor(1., 1., 1., 1.);
    }


    void
    OpenglUi::render(void) {
        base::corelog() << base::log_level(base::LOG_INFO)
                        << "Starting rendering\n";
        glClear(GL_COLOR_BUFFER_BIT);

        draw_elements_();

        glfwSwapBuffers(window_);
        glfwPollEvents();

        base::corelog() << base::log_level(base::LOG_INFO)
                        << "Rendering ended\n";
    }


    double
    OpenglUi::normalize_xcoord(int64_t x_coord) {
        const base::ConfigMap& cfg = base::SysConfig::instance();
        ASSERT(cfg.get("size_x") > 0);
        return x_coord / (double)cfg.get("size_x");
    }


    double
    OpenglUi::normalize_ycoord(int64_t y_coord) {
        const base::ConfigMap& cfg = base::SysConfig::instance();
        ASSERT(cfg.get("size_y") > 0);
        return y_coord / (double)cfg.get("size_y");
    }


    double
    OpenglUi::normalize_rgb(uint8_t val) {
        return val / (double) ((1 << sizeof(val)) - 1);
    }

    GLint
    OpenglUi::uniform_color_location(void) {
        return glGetUniformLocation(default_program_, "triang_color");
    }


    GLint
    OpenglUi::uniform_transform_location(void) {
        return glGetUniformLocation(default_program_, "trans");
    }


    std::shared_ptr<UiElement>
    OpenglUi::create_polygon(std::vector<std::pair<int64_t, int64_t> > vertices,
                             UiColor color) {
        std::shared_ptr<UiElement> obj(new OpenglUiPolygon(this, vertices,
                                                           color));

        this->register_element(obj);
        return obj;
    }


    void
    OpenglUi::glfw_err_callback_(int error_code, const char * desc) {
        base::corelog() << base::log_level(base::LOG_ERR)
                      << "Error from Lib GLFW. "
                      << "\nError code: " << error_code
                      << "\nError description: " << desc << '\n';
    }


    bool
    OpenglUi::ui_exited(void) {
        return glfwWindowShouldClose(window_);
    }


    GLuint
    OpenglUi::create_program_(const std::string& vert_shader_path,
                              const std::string& frag_shader_path) {
        GLuint vert_shader = create_shader_(vert_shader_path,
                                            GL_VERTEX_SHADER);
        GLuint frag_shader = create_shader_(frag_shader_path,
                                            GL_FRAGMENT_SHADER);
        GLuint program = glCreateProgram();

        glAttachShader(program, vert_shader);
        glAttachShader(program, frag_shader);
        glLinkProgram(program);

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);

        return program;
    }


    GLuint
    OpenglUi::create_shader_(const std::string& shader_path,
                             GLenum shader_type) {
        GLuint shader_id = glCreateShader(shader_type);
        std::string shader_src = get_shader_src_(shader_path);
        const char * raw_shader_src = shader_src.c_str();
        glShaderSource(shader_id, 1, &raw_shader_src, nullptr);
        glCompileShader(shader_id);

        GLint compile_status;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

        if(GL_TRUE != compile_status) {
            char buff[512];
            glGetShaderInfoLog(shader_id, 512, nullptr, buff);
            base::corelog() << base::log_level(base::LOG_ERR)
                            << "OpenGL Shader compilation failed. Description:"
                            << buff;
        }

        return shader_id;
    }


    std::string
    OpenglUi::get_shader_src_(const std::string &filepath) {
        std::ifstream ifs;
        std::string line;
        std::stringstream ss;
        ifs.open(filepath);

        while(getline(ifs, line)) {
            ss << line << '\n';
        }
        ifs.close();

        return ss.str();
    }


    OpenglUiPolygon::OpenglUiPolygon(
        OpenglUi* ui,
        std::vector<std::pair<int64_t, int64_t> > vertices,
        UiColor color)
        :ui_(ui), color_(color), vertices_(vertices) {
        base::corelog() << base::log_level(base::LOG_INFO)
                        << "Creating polygon\n";

        vertices_gl_.clear();

        for(size_t i = 0; i < vertices.size(); ++i) {
            vertices_gl_.push_back(ui->normalize_xcoord(vertices[i].first));
            vertices_gl_.push_back(ui->normalize_ycoord(vertices[i].second));
        }

        glGenVertexArrays(1, &vao_id_);
        glBindVertexArray(vao_id_);

        glGenBuffers(1, &vbo_id_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);

        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(vertices_gl_[0]) * vertices_gl_.size(),
                     &vertices_gl_[0],
                     GL_STATIC_DRAW);


        base::corelog() << base::log_level(base::LOG_INFO)
                        << "Created polygon\n";
    }


    void
    OpenglUiPolygon::draw(void) {
        base::corelog() << base::log_level(base::LOG_INFO)
                        << "Drawing polygon " << id_ << '\n';

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        GLint uni_color = ui_->uniform_color_location();

        glUniform3f(uni_color, ui_->normalize_rgb(color_.r()),
                    ui_->normalize_rgb(color_.g()),
                    ui_->normalize_rgb(color_.b()));

        // transform_ = glm::rotate(transform_, glm::radians(180.f),
        //                          glm::vec3(.0f, .0f, 1.f));

        GLint uni_trans = ui_->uniform_transform_location();
        glUniformMatrix4fv(uni_trans, 1, GL_FALSE, glm::value_ptr(transform_));



        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices_.size());
        //glDrawElements(GL_TRIANGLES, elements_gl_.size(), GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);


        base::corelog() << base::log_level(base::LOG_INFO)
                        << "Drew polygon " << id_ << '\n';
    }
}
