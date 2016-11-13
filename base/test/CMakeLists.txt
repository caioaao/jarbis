add_executable(jarbis_base_test ConfigTest.cc LoggerTest.cc LinAlgTest.cc main.cc)
target_link_libraries(jarbis_base_test jarbis_base)
