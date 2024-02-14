#include "Filesystem.h"
#include "OxygenPCH.h"
#include "Filesystem.h"

#include "Platform/Platform.h"

#include <fstream>

namespace oxygen
{
	auto Filesystem::ReadFile(std::string_view path) const -> std::vector<oxyU8>
	{
		std::string pathFull{path}; // WHy???
		std::ifstream fileStream{pathFull, std::ios::binary};
		if (!fileStream.is_open())
			return {};

		fileStream.seekg(0, std::ios::end);
		const auto fileSize = fileStream.tellg();
		fileStream.seekg(0, std::ios::beg);

		std::vector<oxyU8> fileData{};
		fileData.resize(fileSize);
		fileStream.read(reinterpret_cast<char*>(fileData.data()), fileSize);
		fileStream.close();

		return fileData;
	}
	auto
	Filesystem::ReadFileFromExecutableDirectory(std::string_view path) const
		-> std::vector<oxyU8>
	{
		std::string pathFull{GetApplicationDirectory()};
		pathFull += '/';
		pathFull += path;
		return ReadFile(pathFull);
	}
}; // namespace oxygen