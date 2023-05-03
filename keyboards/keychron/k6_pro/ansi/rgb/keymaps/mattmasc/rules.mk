VIA_ENABLE = yes
OPT_DEFS += -DDYNAMIC_KEYMAP_LAYER_COUNT=12
LTO_ENABLE = yes
CAPS_WORD_ENABLE = yes
AUTOCORRECT_ENABLE = yes
SRC += features/achordion.c
SRC += features/select_word.c
SRC += features/mouse_turbo_click.c

MOUSEKEY_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
TAP_DANCE_ENABLE = yes
