
#pragma once

#include <iostream>

class Console {

public:
    void log(const std::string& mes) {
        std::cout << mes << std::endl;
    }
	void warn(const std::string& mes) {
		std::cerr << "Warning: " << mes << std::endl;
	}
	void error(const std::string& mes) {
		std::cerr << "Error: " << mes << std::endl;
	}
};
