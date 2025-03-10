
#include <opencv2/opencv.hpp>
#include <vector>
#include "ImageObject.h"
#include "SettingFile.h"
#include "Performance.h"
#include "../OpenCV/OpenCV.h"
#include "../Custom/Custom.h"

#pragma comment(lib, "OpenCV.lib")
#pragma comment(lib, "Custom.lib")

int main(void)
{
	SettingData setting = SettingFile::Read();
	int size = setting.img_paths.size();

	std::vector<ImageObject> src(size);
	std::vector<ImageObject> opencv_dst(size);
	std::vector<ImageObject> custom_dst(size);
	Performance pOpencv, pCustom;

	for (int i = 0; i < size; i++) {
		src[i].load(setting.img_paths[i]);
	}

	/*opencv blur*/
	pOpencv.start();
	for (int i = 0; i < size; i++) {
		OpenCV::ImageBlur(&src[i], &opencv_dst[i], 21);
	}
	pOpencv.stop();
	Log::log(std::format("Performance opencv time - {} s", pOpencv.getProcessingTime()));
	Log::log(std::format("Performance opencv memory - {} KB", pOpencv.getMemoryUsage()));

	/*custom blur*/
	pCustom.start();
	for (int i = 0; i < size; i++) {
		Custom::ImageBlur(&src[i], &custom_dst[i], 21);
	}
	pCustom.stop();
	Log::log(std::format("Performance custom time - {} s", pCustom.getProcessingTime()));
	Log::log(std::format("Performance custom memory - {} KB", pCustom.getMemoryUsage()));

	/* save */
	for (int i = 0; i < size; i++) {
		std::string path = setting.img_paths[i];
		size_t p = path.find_last_of('/');
		std::string file = (p == std::string::npos) ? path : path.substr(p + 1);

		opencv_dst[i].save(setting.save_path + "/opencv_" + file);
		custom_dst[i].save(setting.save_path + "/custom_" + file);
	}

	return 0;
}