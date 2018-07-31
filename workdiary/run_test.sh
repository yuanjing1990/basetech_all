#!/bin/bash
#usage:
#	./run_test.sh MODULE_NAME
MODULE_NAME=$1
./build_test.sh ${MODULE_NAME}
gnome-terminal -t "emulator" --working-directory=$PWD -x bash -c "./start_emulator.sh;exec bash"&
sleep 10
./push_test_program.sh ${MODULE_NAME}
