# My build of dwm

## Installation

```bash
sudo make clean install
```

## Usage

I keep a readme in `dwm.pdf` for my whole system, including the binds here.
Press <kbd>super+F1</kbd> to view it in dwm (zathura is required for that binding).
I haven't kept `man dwm`/`dwm.1` updated though. 

## Patches and features

Extra stuff added to vanilla dwm into order of the applied patches:

1. [dwm-vanitygaps-6.2](https://dwm.suckless.org/patches/vanitygaps/dwm-vanitygaps-6.2.diff): gaps allowed across all layouts.
  - Added layouts: tile, bstack, bstackhoriz, centeredmaster, centeredfloatingmaster, deck, fibonacci (dwindle, spiral), grid, nrowgrid.
  - All bound to keys <kbd>super+(shift+)t/y/u/i</kbd>.
2. [dwm-swallow-6.3](https://dwm.suckless.org/patches/swallow/dwm-swallow-6.3.diff): if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
3. [dwm-pertag-20200914-61bb8b2](https://dwm.suckless.org/patches/pertag/dwm-pertag-20200914-61bb8b2.diff): this patch keeps selected layout per tag.
4. [dwm-stacker-6.2](https://dwm.suckless.org/patches/stacker/dwm-stacker-6.2.diff): move windows up the stack manually (<kbd>super-K/J</kbd>).
5. [dwm-statusallmons-6.2](https://dwm.suckless.org/patches/statusallmons/dwm-statusallmons-6.2.diff): draws and updates the statusbar on all monitors.
6. [dwm-sticky-6.4](https://dwm.suckless.org/patches/sticky/dwm-sticky-6.4.diff): press <kbd>super+s</kbd> to make/unmake a window 'sticky'. A sticky window is visible on all tags.
7. [shiftview](https://dwm.suckless.org/patches/nextprev/): Cycle through tags (<kbd>super+g/;</kbd>).
8. [dwm-scratchpads-20200414-728d397b](https://dwm.suckless.org/patches/scratchpads/dwm-scratchpads-20200414-728d397b.diff): accessible with <kbd>mod+shift+enter</kbd>.
9. [dwm-actualfullscreen-20211013-cb3f58a](https://dwm.suckless.org/patches/actualfullscreen/dwm-actualfullscreen-20211013-cb3f58a.diff): true fullscreen (<kbd>super+f</kbd>) and prevents focus shifting.
10. [dwm-hide_vacant_tags-6.3](https://dwm.suckless.org/patches/hide_vacant_tags/dwm-hide_vacant_tags-6.3.diff): hides tags with no windows.
11. [dwm-statuscmd-20210405-67d76bd](https://dwm.suckless.org/patches/statuscmd/dwm-statuscmd-20210405-67d76bd.diff): with my build of [dwmblocks](https://github.com/v01dv/dwmblocks).
12. [dwm-xresources-20210827-138b405](https://dwm.suckless.org/patches/xresources/dwm-xresources-20210827-138b405.diff): reads colors/variables.

## TODO

- [ ] Update and replace dwm.pdf with my document (create dwm.md and then convert it to pdf).
- [ ] [three-column](https://dwm.suckless.org/patches/three-column/) patch adds Three Column Layout with a wide master panel centered on the screen.
- [ ] [tatami](https://dwm.suckless.org/patches/tatami/): this patch adds a new layout, tatami, that arranges all windows like tatami tiles.

## Credits

- [LukeSmithxyz](https://github.com/LukeSmithxyz/dwm)
