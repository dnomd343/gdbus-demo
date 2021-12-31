cmake_minimum_required(VERSION 3.16)

EXECUTE_PROCESS(COMMAND gdbus-codegen --generate-c-code
        ${PROJECT_SOURCE_DIR}/gdbus/gdbus_demo_gen ${PROJECT_SOURCE_DIR}/gdbus/interface.xml)
