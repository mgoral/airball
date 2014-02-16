#!/bin/sh

stepError() {
    echo "--------------------------"
    echo "An error occured during step $1"
    echo "Exiting"
    echo "--------------------------"
    exit 1
}

echo "Preparing Airball build system..."

echo "Preparing necessary git submodules..."
git submodule update --init || stepError "submodules"
