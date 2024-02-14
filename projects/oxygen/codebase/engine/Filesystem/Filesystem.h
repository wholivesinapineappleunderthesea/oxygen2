#pragma once

namespace oxygen
{
	struct Filesystem : SingletonBase<Filesystem>
	{
		auto ReadFile(std::string_view path) const
			-> std::vector<oxyU8>;
		auto ReadFileFromExecutableDirectory(std::string_view path) const
			-> std::vector<oxyU8>;
	};
}; // namespace oxygen