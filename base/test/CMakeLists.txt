add_executable(JarbisBaseTest ConfigTest.cc LoggerTest.cc LinAlgTest.cc main.cc)
target_link_libraries(JarbisBaseTest JarbisBase)
