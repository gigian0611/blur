#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <assert.h>

struct SettingData
{
    std::vector<std::string> img_paths;
    std::string save_path;
    int kernel_size;
};

struct SettingFile
{
public :
    inline static constexpr const char* SETTING_FILE = "setting.txt";

    static const SettingData Read()
    {
        std::ifstream file(SETTING_FILE);
        assert(file.is_open());

        SettingData setting;

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream is_line(line);
            std::string key;
            if (std::getline(is_line, key, '=')) {
                std::string value;
                if (std::getline(is_line, value)) {
                    line = value;
                    if (!key.compare("images")) {
                        std::istringstream is_line2(line);
                        while (std::getline(is_line2, value, ',')) {
                            setting.img_paths.push_back(value);
                        }
                    }
                    else if (!key.compare("savepath")) {
                        setting.save_path = value;
                    }
                    else if (!key.compare("kernel")) {
                        setting.kernel_size = std::stoi(value);
                    }
                }
            }
        }
        return setting;
    }

};