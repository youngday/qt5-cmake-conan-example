from conans import ConanFile, CMake


class ImguiOpencvDemo(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = \
        "fmt/8.1.1",\
        "boost/1.79.0",\
        "spdlog/1.10.0",\
        "nlohmann_json/3.10.5",\
        "tomlplusplus/2.5.0",\
        "openssl/1.1.1o",\
        "asio/1.22.1",\
        "cpr/1.8.1",\
        "numcpp/2.7.0",\
        "xtensor/0.24.0",\
        "opencv/4.5.5",\
        "implot/0.13",\
        "trantor/1.5.5",\
        "drogon/1.7.5",\
        "concurrentqueue/1.0.3"#,\
        #"drogon/1.7.5" ，\
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")

