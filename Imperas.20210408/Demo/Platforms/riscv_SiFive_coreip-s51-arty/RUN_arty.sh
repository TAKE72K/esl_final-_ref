#!/bin/bash

# Check Installation supports the base requirements for this example
checkinstall.exe -p install.pkg --nobanner || exit

apps=$(ls examples/*.elf | sort -d)
PS3='Please Choose Vector Example: '
select app in $apps
do
    break
done
echo "Selected Example $app"

if [ "$app" = "examples/local-interrupt.elf" ]; then
  echo "** Connect to HTTP Visualization port using http://localhost:8000 in browser"
fi

harness.exe \
    --modulevendor sifive.ovpworld.org --modulename coreip-s51-arty \
    --program ${app} \
    --output imperas.log \
    --verbose \
    \
    --override coreip-s51-arty/uart/console=T \
    --override coreip-s51-arty/uart/outfile=uart.log \
    \
    --httpvis \
    \
    "$@"

echo "** See UART Output in uart.log **"
