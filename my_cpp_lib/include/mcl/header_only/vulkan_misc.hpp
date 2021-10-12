/*
* vulkan杂项工具
*/

#pragma once
#include <vector>
#include <vulkan/vulkan.hpp>


// 检查vulkan指定扩展是否存在
inline static
std::vector<bool> check_exist_exts(const std::vector<vk::ExtensionProperties>& exts,
	const std::vector<std::string>& wait_check_exts)
{
	std::vector<bool> is_exists(wait_check_exts.size(), false);
	for (int i = 0; i < wait_check_exts.size(); ++i)
	{
		for (auto ext : exts)
			if (ext.extensionName == wait_check_exts[i])
			{
				is_exists[i] = true;
				break;
			}
	}
	return is_exists;
}


// 检查vulkan指定扩展层是否存在
inline static
std::vector<bool> check_exist_layers(const std::vector<vk::LayerProperties>& layers,
	const std::vector<std::string>& wait_check_layers)
{
	std::vector<bool> is_exists(wait_check_layers.size(), false);
	for (int i = 0; i < wait_check_layers.size(); ++i)
	{
		for (auto layer : layers)
			if (layer.layerName == wait_check_layers[i])
			{
				is_exists[i] = true;
				break;
			}
	}
	return is_exists;
}
