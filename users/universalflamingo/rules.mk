
ifeq ($(strip $(KEYBOARD)), ploopyco/trackball_thumb/rev1_001)

CONSOLE_ENABLE = no
EXTRAKEY_ENABLE = no
LTO_ENABLE = yes
MOUSEKEY_ENABLE = no
NKRO_ENABLE = no
VIA_ENABLE = yes

SRC += trackball_thumb.c

endif
