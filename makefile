lightdm_sandbox_greeter:lightdm_sandbox_greeter.c
	gcc -o lightdm_sandbox_greeter lightdm_sandbox_greeter.c `pkg-config --libs --cflags gtk+-3.0 liblightdm-gobject-1 gmodule-export-2.0`

clean: 
	rm -vf lightdm_sandbox_greeter
