#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

struct Log
{
public:
    inline static constexpr const char* LOG_FILE_FOLDER = "log/";
    inline static constexpr const char* LOG_FILE_NAME = "log.txt";

    static const void log(const std::string message) {

        if (!std::filesystem::exists(LOG_FILE_FOLDER)) {
            std::filesystem::create_directories(LOG_FILE_FOLDER);
        }

        std::ofstream file(std::format("{}{}", LOG_FILE_FOLDER, LOG_FILE_NAME), std::ios_base::app);
        assert(file.is_open());
        file << getCurrentTime() + " : " + message << std::endl;
    }

    static const std::string getCurrentTime() {
        time_t now = time(nullptr); 
        std::tm local_tm;
        localtime_s(&local_tm, &now); 

        char buffer[30];
        strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", &local_tm);
        return std::string(buffer);
    }

};

class ImageObject
{
public : 
    inline static constexpr int CHANNEL = 1;

private :
    int width = 0;
    int height = 0;
    std::vector<unsigned char> buffer;
    std::string path;
public :
    ImageObject() = default;

    void load(const std::string filepath) 
    {
        path = filepath;
        cv::Mat img = cv::imread(filepath, cv::IMREAD_GRAYSCALE);
        assert(!img.empty());
        assert(img.channels() == CHANNEL);
        *this = img;

        Log::log(filepath + " file load");
    }

    void save(const std::string filepath) const 
    {
        assert(!buffer.empty());
        cv::Mat img = *this;

        size_t p = filepath.find_last_of('/');
        std::string directory = (p != std::string::npos) ? filepath.substr(0, p + 1) : "";

        if (!std::filesystem::exists(directory)) {
            std::filesystem::create_directories(directory);
        }

        cv::imwrite(filepath, img);

        Log::log(filepath + " file save");
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    std::string getPath() const { return path; }

    ImageObject& operator=(const cv::Mat& img) 
    {
        if (img.empty())
            return *this;
        width = img.cols;
        height = img.rows;
        buffer.assign(img.data, img.data + (width * height * CHANNEL));
        return *this;
    }

    operator cv::Mat() const 
    {
        if (buffer.empty())
            return cv::Mat();
        return cv::Mat(height, width, CV_8UC1, (void*)buffer.data()).clone();
    }

    ImageObject& operator=(const std::vector<unsigned char>& data)
    {
        buffer = data;
        return *this;
    }

    void resize(int size, int width, int height)
    {
        this->width = width;
        this->height = height;
        buffer.assign(size, 0);
    }

    operator std::vector<unsigned char>& () {
        return buffer;
    }

    operator const std::vector<unsigned char>& () const {
        return buffer;
    }
};

