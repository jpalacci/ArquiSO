include Makefile.inc

SAMPLE_DATA=0001-sampleDataModule.bin

all: dummy sampleCodeModule sampleDataModule 
dummy:
	cd dummy; make
sampleCodeModule:
	cd SampleCodeModule; make

sampleDataModule:
	printf "This is sample data." >> $(SAMPLE_DATA) && dd if=/dev/zero bs=1 count=1 >> $(SAMPLE_DATA)

clean:
	cd SampleCodeModule; make clean
	cd dummy; make clean
	rm -rf *.bin


.PHONY: dummy SampleCodeModule all clean
