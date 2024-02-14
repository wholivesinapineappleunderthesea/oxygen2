#pragma once

// assert
#include <cassert>

// memory
#include <new> 
#include <memory>

// util
#include <utility>

// execution
#include <execution>

// algorithm/ranges
#include <ranges>
#include <algorithm>

// containers
#include <optional>
#include <variant>
#include <array>
#include <string>
#include <vector>
#include <unordered_map>

// spans
#include <string_view>
#include <span>

// math
#include <cmath>
#include <limits>

// random
#include <random>

// Engine macros
#ifdef _MSC_VER
#define OXYDEBUGBREAK() __debugbreak()
#else
#define OXYDEBUGBREAK() __builtin_trap()
#endif

/**
 * @brief Asserts if the given expression is false. Does not evaluate the
 * expression in release builds.
 * @param x The expression to assert.
 */
#ifdef OXYDEBUG
#define OXYCHECK(x)                                                            \
	do                                                                         \
	{                                                                          \
		if (!(x))                                                              \
		{                                                                      \
			OXYDEBUGBREAK();                                                   \
		}                                                                      \
	} while (0)
#else
#define OXYCHECK(x)                                                            \
	do                                                                         \
	{                                                                          \
	} while (0)
#endif
/**
 * @brief Asserts if the given expression is false. Evaluates and ignores the
 * result of the expression in release builds.
 * @param x The expression to assert.
 */
#ifdef OXYDEBUG
#define OXYVERIFY(x)                                                           \
	do                                                                         \
	{                                                                          \
		if (!(x))                                                              \
		{                                                                      \
			OXYDEBUGBREAK();                                                   \
		}                                                                      \
	} while (0)
#else
#define OXYVERIFY(x)                                                           \
	do                                                                         \
	{                                                                          \
		x;                                                                     \
	} while (0)
#endif

// Engine headers
#include "OxygenTypes.h"
#include "Hash/CRC64.h"
#include "Object/Object.h"
#include "Object/ManagedObject.h"
#include "Object/ObjectManager.h"
