find_package(Catch2 REQUIRED)

#function to append extensions
FUNCTION(APPEND_EXT var source ext)
	SET(listVar "")
	FOREACH(f ${${source}})
		LIST(APPEND listVar "${f}.${ext}")
	ENDFOREACH(f)
	SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(APPEND_EXT)

set(TESTS
	list
)

APPEND_EXT(TESTS TESTS "cpp")

add_executable(unit-tests main.cpp ${TESTS})
set_target_properties(unit-tests PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:unit-tests>")
target_link_libraries(unit-tests PRIVATE Catch2::Catch2 SpatialOrganizer)

add_custom_command(TARGET unit-tests POST_BUILD
	COMMAND unit-tests [unit]
)

set_target_properties(unit-tests PROPERTIES FOLDER "Tests")