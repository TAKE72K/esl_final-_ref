#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C applicationSend           CROSS=OR1K
make -C applicationSendForever    CROSS=OR1K
make -C applicationReceive        CROSS=OR1K
make -C module

echo First platform: Server which sends bytes to socket.

harness.exe \
    --modulefile module/model \
    --program    applicationSend/application.OR1K.elf  \
    --override   simpleCpuMemoryUart/periph0/client=0  \
    --override   simpleCpuMemoryUart/periph0/portnum=0 \
    --override   simpleCpuMemoryUart/periph0/portFile=portNumber.txt \
    --output     server.log \
    &

declare -i count=0
while [ ! -f portNumber.txt ]; do
  count=$(($count + 1))
  if [ $count -ge 30 ]; then 
    echo "Did not find GDB port, exiting ..."
    exit 1
  fi
  sleep 1
done

PORTNUM=$(cat portNumber.txt)
  
echo Second platform: client which reads bytes from socket.

harness.exe \
    --modulefile module/model \
    --program    applicationReceive/application.OR1K.elf  \
    --override   simpleCpuMemoryUart/periph0/client=1  \
    --override   simpleCpuMemoryUart/periph0/portnum=$PORTNUM \
    --override   simpleCpuMemoryUart/periph0/hostname=localhost \
    --override   simpleCpuMemoryUart/periph0/finishOnDisconnect=1 \
    --output     client.log
    

