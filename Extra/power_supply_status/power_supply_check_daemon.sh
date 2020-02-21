#!/bin/sh

do_start() {
	echo "Starting power_supply_check script...";
	/sbin/power_supply_check_daemon 
}

do_start
