#!/bin/bash

HWDEF=${IMPERAS_HOME}/ImperasLib/source/imperas.ovpworld.org/platform/SiFiveFU540/1.0/platform

if [ -d $HWDEF ]; then

  ANSWER=
  echo "Open a browser on platform directory [y/N]"

  read ANSWER
  if [ "${ANSWER}" = "y" ] || [ "${ANSWER}" = "Y" ] ; then

    if [ -x /usr/bin/firefox ]; then
      firefox file:${HWDEF}
    else
      echo "Open directory ${HWDEF} in a terminal to view platform source"
    fi
  fi
else
  echo "Not found platform source in this installation, please check required installation packages for $HWDEF" 
fi