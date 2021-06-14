#!/bin/bash

HWDEF=${IMPERAS_HOME}/ImperasLib/source/andes.ovpworld.org/module/AE350/1.0/module

if [ -d $HWDEF ]; then

  ANSWER=
  echo "Open a browser on module directory [y/N]"

  read ANSWER
  if [ "${ANSWER}" = "y" ] || [ "${ANSWER}" = "Y" ] ; then

    if [ -x /usr/bin/firefox ]; then
      firefox file:${HWDEF}
    else
      echo "Open directory ${HWDEF} in a terminal to view module source"
    fi
  fi
else
  echo "Not found module source in this installation, please check required installation packages for $HWDEF" 
fi