
include_directories(${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )

add_subdirectory(communication)
add_subdirectory(hearts)
add_subdirectory(general)
add_subdirectory(network)


########### install files ###############




#original Makefile.am contents follow:

#AUTOMAKE_OPTIONS = foreign
#SUBDIRS = communication hearts general network
#
