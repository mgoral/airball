#!/bin/sh

echo "Preparing Airball build system..."

autoreconf --force --install
autorecst=$?

if [ $autorecst -ne 0 ]; then
    echo ""
    echo "*** An ERROR occured on autoreconf! Check if there's a UNIX guru nearby to help you. ***"
    exit 1
fi

#
# Uncommented until there's no need for gettext
#

#intltoolize --force
#intltoolst=$?
#if [ $intltoolst -ne 0 ]; then
#    echo ""
#    echo "*** An ERROR occured on intltoolize! Is it installed on your system? ***"
#    exit 1
#fi

echo ""
echo "*** Build system ready. ***"
echo ""
