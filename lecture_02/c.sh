#!/bin/bash

echo command $0
echo first four args $1 $2 $3 $4
echo all args $@
echo all args $*
echo nr args $#

echo ======================================
shift 5
echo first four args $1 $2 $3 $4

