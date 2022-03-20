#pragma once
#ifndef __DIR_H__
#define __DIR_H__
#include <string>
#include <filesystem>

namespace dir 
{
	template<typename... T>
	inline std::string root(const T&... filepath) {
		std::filesystem::path root_path(".");
		(root_path.append(filepath), ...);
		root_path /= "";
		return root_path.string();
	}
	template<typename... T>
	inline std::string image(const T&... filepath) {
		std::filesystem::path img_path("./data/image");
		(img_path.append(filepath), ...);
		img_path /= "";
		create_directories(img_path);
		return img_path.string();
	}
	template<typename... T>
	inline std::string app(const T&... filepath) {
		std::filesystem::path app_path("./data/app");
		(app_path.append(filepath), ...);
		app_path /= "";
		create_directories(app_path);
		return app_path.string();
	}
	template<typename... T>
	inline std::string app_config(const T&... filepath) {
		std::filesystem::path app_config_path("./data/app");
		app_config_path.append("Config");
		(app_config_path.append(filepath), ...);
		app_config_path /= "";
		create_directories(app_config_path);
		return app_config_path.string();
	}
}
#endif // !__DIR_H__
