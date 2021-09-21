set(SANDBOX_SOURCES
	"SandboxApp.cpp"
)

add_executable(Sandbox
	${SANDBOX_SOURCES}
)

target_link_libraries(Sandbox PRIVATE 
	Quark
)

add_custom_command(TARGET Sandbox POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Quark> $<TARGET_FILE_DIR:Sandbox>
)