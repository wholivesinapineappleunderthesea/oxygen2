#pragma once

namespace oxygen
{
	/**
	 * @brief Main implementation 
	 * @param argc Argument count
	 * @param argv Argument values
	 * @return Exit code
	*/
	auto Main(int argc, char* argv[]) -> int;

	/**
	 * @brief Get the current platform-defined high resolution time
	 * @return Current time
	*/
	auto GetHighPrecisionTime() -> oxyU64;
	/**
	 * @brief Convert a high resolution time to seconds
	 * @param time Time to convert
	 * @return Time in seconds
	*/
	auto HighPrecisionTimeToSeconds(oxyU64 time) -> oxyF64;

	/**
	 * @brief Get the application directory
	 * @return Application (exe) directory
	*/
	auto GetApplicationDirectory() -> std::string_view;

	/**
	 * @brief Get platform window type
	 * @return Platform defined window reference
	*/
	auto GetPlatformWindow() -> void*;

	/**
	 * @brief Get the platform's render context
	 * @return Abstract render context reference
	*/
	auto GetRenderContext() -> struct IRenderContext*;
};