CMAKE_MINIMUM_REQUIRED (VERSION 2.8.6)
PROJECT(silencer)

aux_source_directory(. DIR_SRCS)
set(SOURCE_FILES silencer.c php_silencer.h)

add_executable(silencer ${DIR_SRCS} ${SOURCE_FILES})

# Define path to php-src, change accordingly
set(PHP_SOURCE ../../)
# Import php sources
include_directories(
        ${PHP_SOURCE}
        ${PHP_SOURCE}/main
        ${PHP_SOURCE}/Zend
        ${PHP_SOURCE}/TSRM
        ${PHP_SOURCE}/ext
        ${PHP_SOURCE}/sapi
        ${PHP_SOURCE}/pear
)