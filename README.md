# LiteNESU-16-in-1
A Wii-U NES Emulator

LiteNESU 16-in-1 NES Emulator Elf Version for 5.5.x by brienj

This is a port of QuarkTheAwesome's port of LiteNES. It has 16 NES ROMs (All titles between A and E, plus Yie Ar Kung Fu) built-in that "work" in the emulator. Source code and possibly more versions with different games coming soon(TM).

LiteNESU (QuarkTheAwesome source code): https://github.com/QuarkTheAwesome/LiteNESU
LiteNES source code: https://github.com/NJUOS/LiteNES

This is ONLY for 5.5.x firmware and there will NOT be any other firmware version made. If you have lower than 5.5.x, then go and enjoy your kernel access. If you really want me to make it for your version, then tell people with kernel or IOSU access in 5.5.x to release, since I can not make the game compatible with the homebrew channel at the moment, since I have no way to test. Or just wait until I get kernel or IOSU access on my own.

Setup: Put the ROM files named correctly in the data folder and compile the boot.elf file. Place it on your webserver that has an elf loader or find the elf file hosted somewhere.

Instructions: Launch games or select EXIT with the B Button on the main menu. When in game, D-PAD for movement, A and B button like on an NES. PLUS button is START and MINUS button is SELECT. Pressing the HOME button while in game will return you to the selection menu.

You can press the R button to change the graphics filter.

Full list of titles in this release:
1942 (playable, but graphic glitches on the scrolling playfield)
Arkanoid (no major problems)
Astro Robo Sasa (no major problems)
Balloon Fight (no major problems)
Baltron (scrolling graphic issues)
Battle City (no major problems)
Chack 'n Pop (no major problems)
Defender (scrolling graphic issues)
Dig Dug (graphic glitches, but playable)
Donkey Kong (no major problems)
Donkey Kong Jr (no major problems)
Donkey Kong 3 (no major problems)
Dough Boy (playable, but graphic glitches, can get stuck)
Exed Exes (playable, but scrolling graphic glitches)
Exerion (no major problems, but you can't see background, had to turn off so it didn't crash)
Yie Ar Kung-Fu (no major problems)

I was disappointed that Elevator Action and Excite Bike didn't work, since they should have. I thought Burger Time would have worked too, but it didn't. All of these games have no mapper though, may be able to fix the emulator to play them. Elevator Action's only problem was the graphics not scrolling properly. Baltron and Exerion would crash until I was able to fix it.

Planned to be added: Another version with more games??? GX2 graphics??? A different emulator base??? (No point until kernel or IOSU)
