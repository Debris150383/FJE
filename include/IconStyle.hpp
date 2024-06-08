#pragma once
#include <string>

class Icon {
public:
    std::string name;
    std::string leafIcon;
    std::string containerIcon;

    static Icon& getInstance() {
        static Icon icon;
        return icon;
    }

    Icon(const Icon&) = delete;
    void operator=(const Icon&) = delete;

private:
    Icon() {}
};


