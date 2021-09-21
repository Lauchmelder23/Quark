# Build used libraries
add_subdirectory(vendor/spdlog)

# Build Quark
add_subdirectory(src)
target_include_directories(Quark PUBLIC
	"vendor/spdlog/include"
)