#include <iostream>
#include <array>
#include <memory>


std::string exec(const char* cmd) {
    std::array<char, 1024*4> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(int argc, char const *argv[])
{
    std::string dir = argv[1];
    std::cout << exec(("du " + dir + " -sb").c_str()) << std::endl;
    std::string ret = exec(("du " + dir + " -sb").c_str());
    int num = std::stoi(ret);
    float size = ((float)num)/(1024*1024);
    printf("目录 %s 的大小为 %d byte; %.1f m\n",dir.c_str(),num,size);
    return 0;
}
