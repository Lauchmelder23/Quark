set(QUARK_SOURCES 
	"Quark/qkpch.cpp"
	"Quark/Log.cpp"
	"Quark/Application.cpp"
)

set(QUARK_HEADERS
	"Quark.hpp"
	"Quark/Log.hpp"
	"Quark/EntryPoint.hpp"
	"Quark/Core.hpp"
	"Quark/Application.hpp"
	"Quark/Events/Event.hpp"
	"Quark/Events/ApplicationEvent.hpp"
	"Quark/Events/KeyEvent.hpp"
	"Quark/Events/MouseEvent.hpp"
)

add_library(Quark SHARED 
	${QUARK_SOURCES} ${QUARK_HEADERS}
)

target_include_directories(Quark PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

if(WIN32)
	target_compile_definitions(Quark PUBLIC
		QK_PLATFORM_WINDOWS 
	)
	target_compile_definitions(Quark PRIVATE 
		QK_BUILD_DLL
	)
endif()