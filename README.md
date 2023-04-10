# My build of dwm

## Installation

```bash
sudo make clean install
```

## Usage

I keep a readme in `dwm.pdf` for my whole system, including the binds here.
Press `super+F1` to view it in dwm (zathura is required for that binding).
I haven't kept `man dwm`/`dwm.1` updated though. 

## Patches and features

Extra stuff added to vanilla dwm (version 6.4) into order of the applied patches:

1. [dwm-vanitygaps-6.2](https://dwm.suckless.org/patches/vanitygaps/dwm-vanitygaps-6.2.diff): gaps allowed across all layouts.
    - Added layouts: tile, bstack, bstackhoriz, centeredmaster, centeredfloatingmaster, deck, fibonacci (dwindle, spiral), grid, nrowgrid.
    - All bound to keys `super+(shift+)t/y/u/i`.
2. [dwm-swallow-6.3](https://dwm.suckless.org/patches/swallow/dwm-swallow-6.3.diff): if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
3. [dwm-pertag-20200914-61bb8b2](https://dwm.suckless.org/patches/pertag/dwm-pertag-20200914-61bb8b2.diff): this patch keeps selected layout per tag.
4. [dwm-stacker-6.2](https://dwm.suckless.org/patches/stacker/dwm-stacker-6.2.diff): move windows up the stack manually (`super-K/J`).
5. [dwm-statusallmons-6.2](https://dwm.suckless.org/patches/statusallmons/dwm-statusallmons-6.2.diff): draws and updates the statusbar on all monitors.
6. [dwm-sticky-6.4](https://dwm.suckless.org/patches/sticky/dwm-sticky-6.4.diff): press `super+s` to make/unmake a window 'sticky'. A sticky window is visible on all tags.
7. [shiftview](https://dwm.suckless.org/patches/nextprev/): Cycle through tags (`super+g/;`).
8. [dwm-scratchpads-20200414-728d397b](https://dwm.suckless.org/patches/scratchpads/dwm-scratchpads-20200414-728d397b.diff): accessible with `mod+shift+enter`.
9. [dwm-actualfullscreen-20211013-cb3f58a](https://dwm.suckless.org/patches/actualfullscreen/dwm-actualfullscreen-20211013-cb3f58a.diff): true fullscreen (`super+f`) and prevents focus shifting.
10. [dwm-hide_vacant_tags-6.3](https://dwm.suckless.org/patches/hide_vacant_tags/dwm-hide_vacant_tags-6.3.diff): hides tags with no windows.
11. [dwm-statuscmd-20210405-67d76bd](https://dwm.suckless.org/patches/statuscmd/dwm-statuscmd-20210405-67d76bd.diff): with my build of [dwmblocks](https://github.com/v01dv/dwmblocks).
12. [dwm-xresources-20210827-138b405](https://dwm.suckless.org/patches/xresources/dwm-xresources-20210827-138b405.diff): reads colors/variables.

## TODO

- [ ] Update and replace dwm.pdf with my document (create dwm.md and then convert it to pdf).
- [ ] [autostart](https://dwm.suckless.org/patches/autostar). Put autostart stuff in autostart script.
- [ ] [three-column](https://dwm.suckless.org/patches/three-column/): patch adds Three Column Layout with a wide master panel centered on the screen.
- [ ] [tatami](https://dwm.suckless.org/patches/tatami/): this patch adds a new layout, tatami, that arranges all windows like tatami tiles.
- [ ] [attachabove](https://dwm.suckless.org/patches/attachabove/): make new clients attach above the selected client, instead of always becoming the new master.
- [ ] [notitle](https://dwm.suckless.org/patches/notitle/): doesn't show the title.
- [ ] [decoration hints](https://dwm.suckless.org/patches/decoration_hints/): make dwm respect MOTIF_WM_HINTS property, and not draw borders around windows requesting for it.
- [ ] [ewmhtags](https://dwm.suckless.org/patches/ewmhtags/): adds EWMH support for NET_NUMBER_OF_DESKTOPS, NET_CURRENT_DESKTOP, NET_DESKTOP_NAMES, and NET_DESKTOP_VIEWPORT, which allows for compatibility with other bars and programs that request workspace information.
    - https://en.wikipedia.org/wiki/Extended_Window_Manager_Hints
    - https://specifications.freedesktop.org/wm-spec/latest/
    - https://specifications.freedesktop.org/wm-spec/1.5/ar01s03.html
    - https://www.reddit.com/r/suckless/comments/k8lej4/dwm_i_am_looking_for_patches_to_make_dwm_more/

## Credits

- [LukeSmithxyz](https://github.com/LukeSmithxyz/dwm)
