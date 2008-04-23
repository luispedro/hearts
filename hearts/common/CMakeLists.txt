add_subdirectory(communication)
add_subdirectory(hearts)
add_subdirectory(general)
add_subdirectory(network)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${KDE3_INCLUDE_DIR} ${QT_INCLUDE_DIR} )


########### install files ###############




#original Makefile.am contents follow:

#AUTOMAKE_OPTIONS = foreign
#SUBDIRS = communication hearts general network
#
