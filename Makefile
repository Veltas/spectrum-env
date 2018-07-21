.PHONY: all
all: zapp.bin zapp.tap zapp.wav

zapp.wav: zapp.tap
	tape2wav zapp.tap $@

zapp.tap: zapp.bin
	bin2tap -b -o $@ zapp.bin

zapp.bin zapp.lst: *.asm *.c
	zasm -I sdcc/include -L sdcc/lib -y objlayout.asm -l zapp.lst -o zapp.bin

.PHONY: listing
listing: zapp.lst
	less zapp.lst

.PHONY: clean
clean:
	rm -rf *.bin *.lst *.tap *.wav s/
