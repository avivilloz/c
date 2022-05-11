1- open two terminal windows.
2- if nbd devices are not set, do "make nbds" and "make kbs" in any terminal window.
3- do "vim/code/gedit config.txt" in any terminal window, choose your nbd_num.
4- do "make" in first terminal window.
5- do "make run" in first terminal window.
6- do "make dlls" in second terminal window.
7- do "make ext2" or "make ext4" in second terminal window.
8- do "make mount" in second terminal window.
9- place files in "_mount" directory.
10- do "ctr-c" in first terminal window if you wish to stop.
