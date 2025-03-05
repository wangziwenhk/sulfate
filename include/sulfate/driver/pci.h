#pragma once

#include "stdint.h"

namespace sulfate::pci {
    void init_pci();
    /**
     * This function is used to read a 16-bit (word) value from the specified PCI device configuration space
     * @param bus PCI bus number (0-255)
     * @param slot Device Number (0-31)
     * @param func Function Number (0-7)
     * @param offset Offset within the configuration space (0-255)
     * @return A 16-bit value read from configuration space
     */
    uint16_t read_pci_config_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);

    struct PCIDevice {
        uint8_t bus;
        uint8_t slot;
        uint8_t func;
    };

} // namespace sulfate::pci
