#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := sprite.cpp ../MPU6050/sensors.cpp ../MPU6050/MPU6050.cpp

# header files in this project
HEADERS := sprite.hpp vector2i.hpp ../MPU6050/sensors.hpp ../MPU6050/MPU6050.hpp

# other places to look for files for this project
SEARCH  :=

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
