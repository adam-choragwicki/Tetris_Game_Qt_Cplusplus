set(SOURCE_FILES
        game.cpp game.h
        controller.cpp controller.h
        log_manager.cpp log_manager.h
        model/model.h model/model.cpp
        model/active_block_model.cpp model/active_block_model.h
        model/placed_squares_model.cpp model/placed_squares_model.h

        block.h block.cpp
        score_manager.h score_manager.cpp
        placed_squares.h placed_squares.cpp
        square.h
        block_factory.h block_factory.cpp
        block_movement_manager.h block_movement_manager.cpp
        random_generator.h
        coordinates.h coordinates.cpp
        rotation_coefficients.h rotation_coefficients.cpp
        log_manager.h
        rotation_coefficients_database.h
        common.h
        simulation_result.h
        rotation_state.cpp rotation_state.h
        active_block_manager.cpp active_block_manager.h

        # State machine
        state_machine/abstract_state.h
        state_machine/game_state_manager.h
        state_machine/game_state_type.h
        state_machine/i_state_actions.h

        state_machine/states/initialization_state.h
        state_machine/states/ready_to_start_state.h
        state_machine/states/running_state.h
        state_machine/states/escape_menu_state.h
        state_machine/states/ended_state.h

        game_coordinator.cpp game_coordinator.h
        window_manager.cpp window_manager.h

        input_handler.cpp input_handler.h
        overlay_manager.cpp overlay_manager.h

        game_loop.cpp game_loop.h
        config/game_config.h

        speed_level/speed_level.h
        speed_level/speed_level_data.h speed_level/speed_level_data.cpp
        speed_level/speed_level_utils.h

        direction.h
)

add_library(${PROJECT_NAME}Backend ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME}Backend PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}Backend PUBLIC Qt6::Core Qt6::Quick)

target_compile_definitions(${PROJECT_NAME}Backend PRIVATE
        APP_VERSION="${PROJECT_VERSION}"
        BUILD_TYPE="$<CONFIG>"
)

qt_add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Backend TetrisQmlLibplugin)

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>) # this avoids opening console window on Windows in Release mode
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # Set the output directory for the executable
