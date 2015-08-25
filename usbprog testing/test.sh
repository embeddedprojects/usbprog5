#!/bin/bash

python ../client/embeddedprog.py --processor "stm32f1x" --swd on --raw '-c "init;reset halt;stm32f1x mass_erase 0;init;exit;quit"'

python ../client/embeddedprog.py --processor "stm32f1x" --flash-write "/home/eproo/test_swd/EmbSys2-master/Software/0_aufgabe_makefile/main.elf" --swd "on"

echo "##############################################################################\n################################################################################"

python ../client/embeddedprog.py --processor "stm32f1x" --swd on --raw "-c 'init;reset halt;stm32f1x mass_erase 0;init;exit;quit'"


python ../client/embeddedprog.py --processor "stm32f1x" --flash-write "/home/eproo/test_swd/EmbSys2-master/Software/0_aufgabe_makefile/main.elf" --swd "on"
