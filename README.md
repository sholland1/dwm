# Seth's build of dwm

## FAQ

> What are the bindings?

This is suckless, mmmbud, the source code is the documentation! Check out [config.h](config.h).

## Patches and features

- Reads xresources colors/variables (i.e. works with `pywal`, etc.).
- scratchpad: Accessible with mod+shift+enter.
- layouts: tile, bstack, deck, monocle, centeredmaster, centeredfloatingmaster. Cycle through layouts with `super+(shift+)space`.
- stacker: Move windows up the stack manually (`super+shift+k/j`).
- shiftview: Cycle through tags (`super+tab`).
- vanitygaps: Gaps allowed across all layouts.
- swallow patch: if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- preserve on restart: Remember the monitor and tag of windows when restarting dwm.
- focus on net active: Allow programs to request focus.
