#include "sulfate/driver/pci.h"
#include "sulfate/io.h"

using namespace sulfate;

uint16_t pci::read_pci_config_word(const uint8_t bus, const uint8_t slot, const uint8_t func, const uint8_t offset) {
    const auto l_bus = static_cast<uint32_t>(bus);
    const auto l_slot = static_cast<uint32_t>(slot);
    const auto l_func = static_cast<uint32_t>(func);
    uint16_t tmp = 0;

    // Create configuration address as per Figure 1
    const auto address = l_bus << 16 | l_slot << 11 | l_func << 8 | offset & 0xFC | 0x80000000;

    // Write out the address
    io::out32(0xCF8, address);
    // Read in the data
    // (offset & 2) * 8) = 0 will choose the first word of the 32-bit register
    tmp = static_cast<uint16_t>((io::in32(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
    return tmp;
}

void pci::init_pci() {

}
