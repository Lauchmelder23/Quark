set(SANDBOX_SOURCES
	"SandboxApp.cpp"
)

add_executable(Sandbox
	${SANDBOX_SOURCES}
)

target_link_libraries(Sandbox PRIVATE 
	Quark
)

set_property(TARGET Sandbox PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


add_custom_command(TARGET Sandbox POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../assets $<TARGET_FILE_DIR:Sandbox>/assets
)