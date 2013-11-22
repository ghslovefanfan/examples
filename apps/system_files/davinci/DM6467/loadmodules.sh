# insert cmemk, tell it to occupy physical 120MB-128MB, create 
# 20 4K buffers, 10 128K buffers  and two 1MB buffers
insmod cmemk.ko phys_start=0x87800000 phys_end=0x88000000 pools=20x4096,10x131072,2x1048576

# insert dsplinkk
insmod dsplinkk.ko

# make /dev/dsplink
rm -f /dev/dsplink
mknod /dev/dsplink c `awk "\\$2==\"dsplink\" {print \\$1}" /proc/devices` 0

