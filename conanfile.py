from conans import ConanFile, CMake


class ImguiOpencvDemo(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = \
        "fmt/8.1.1",\
        "spdlog/1.10.0",\
        "nlohmann_json/3.10.4",\
        "tomlplusplus/2.5.0",\
        "openssl/1.1.1l",\
        "asio/1.20.0",\
        "cpr/1.7.2",\
        "numcpp/2.7.0",\
        "concurrentqueue/1.0.3"#,\
        #"poco/1.11.0"
#        "eigen/3.4.0",\
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        #self.copy("imgui_impl_glfw.cpp", dst="../src", src="./res/bindings")
        #self.copy("imgui_impl_opengl3.cpp", dst="../src", src="./res/bindings")
        #self.copy("imgui_impl_glfw.h*", dst="../include", src="./res/bindings")
        #self.copy("imgui_impl_opengl3.h*",
         #         dst="../include", src="./res/bindings")
