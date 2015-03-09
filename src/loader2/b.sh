#Workaround -q bug
echo 6 | bochs 'boot:disk' 'ata0-master: type=disk, path=bin/ext2loader.bin, cylinders=1, heads=1, spt=1, status=inserted' 'gdbstub: enabled=1, port=1234, text_base=0, data_base=0, bss_base=0' 'plugin_ctrl: speaker=0' 'debug: action=ignore' 'info: action=ignore' 'error: action=fatal' 'panic: action=fatal'
