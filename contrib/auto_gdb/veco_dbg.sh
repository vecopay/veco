#!/bin/bash
# use testnet settings,  if you need mainnet,  use ~/.vecocore/vecod.pid file instead
veco_pid=$(<~/.vecocore/testnet3/vecod.pid)
sudo gdb -batch -ex "source debug.gdb" vecod ${veco_pid}
