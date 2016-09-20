1. Modyfikacja autostrartu GUI

vim ~/.config/lxsession/LXDE-pi/autostart

#@lxpanel --profile LXDE-pi
#@pcmanfm --desktop --profile LXDE-pi
#@xscreensaver -no-splash
@/usr/bin/python %%PATH_TO_DISPLAYER_PY%%
