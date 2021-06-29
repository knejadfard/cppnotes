# QEMU
QEMU is a generic and open-source machine emulator and virtualizer.
Website: https://www.qemu.org

## Building QEMU From Source
```
../configure --target-list=i386-linux-user,i386-softmmu,x86_64-linux-user,x86_64-softmmu,riscv32-softmmu,riscv64-softmmu --enable-system --enable-sdl --enable-gtk --enable-vte --enable-kvm --enable-bzip2 --enable-linux-user --enable-docs --enable-gnutls --enable-nettle --enable-curses --enable-modules --enable-virtfs --enable-curl --enable-fdt --enable-rdma --enable-vde --enable-linux-aio --enable-cap-ng --enable-attr --enable-vhost-net --enable-spice --enable-rbd --enable-libiscsi --enable-libnfs --enable-smartcard --enable-libusb --enable-usb-redir --enable-lzo --enable-snappy --enable-seccomp --enable-coroutine-pool --enable-glusterfs --enable-tpm --enable-numa --enable-tcmalloc --prefix=/path/to/destination/qemu
```
