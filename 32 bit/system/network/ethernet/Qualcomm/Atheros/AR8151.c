procedure initialize_Qualcomm_Atheros_AR8151_network_device (Network_Device *network_device, PCI_Device *device)
{
    N_32 i;

    N_32 BARs[6];

	write_null_terminated_byte_array(&debug_output, "Qualcomm Atheros AR8151 found\n");

    for(i=0; i<6; ++i)
    {
        BARs[i] = read_from_PCI_device_config(device, 0x10 + i * 4) & 0b11111111111111111111111111110000;

        if(BARs[i] & 1)
        	write_null_terminated_byte_array(&debug_output, "memory i/o ");
        else
        	write_null_terminated_byte_array(&debug_output, "i/o ");

        write_hex_N_32(&debug_output, BARs[i]);
        write_byte(&debug_output, '\n');
    }

    Byte MAC_address[6];

    copy_memory(MAC_address, BARs[0] + MAC_ADDRESS_QUALCOMM_ATHEROS_AR8151, 6);

    write_null_terminated_byte_array(&debug_output, "MAC address ");
    write_hex_array(&debug_output, MAC_address, 6);
/*
    N_32 *GPHY_controller = BARs[0] + GPHY_CONTROLLER_QUALCOMM_ATHEROS_AR8151;

    *GPHY_controller |= LED_MODE_GPHY_CONTROLLER_QUALCOMM_ATHEROS_AR8151;

    N_32 *REG_link_controller = BARs[0] + REG_LINK_CTRL;

    write_byte(&debug_output, '\n');
    write_null_terminated_byte_array(&debug_output, "REG_LINK_CTRL old ");
    write_hex_N_32(&debug_output, *REG_link_controller);
    *REG_link_controller |= LINK_CTRL_L0S_EN;
    write_null_terminated_byte_array(&debug_output, " new ");
    write_hex_N_32(&debug_output, *REG_link_controller);

    N_32 *MDIO_control_register = BARs[0] + REG_MDIO_CTRL;

    write_byte(&debug_output, '\n');
    write_null_terminated_byte_array(&debug_output, "REG_MDIO_CTRL old ");
    write_hex_N_32(&debug_output, *MDIO_control_register);
    *MDIO_control_register |=
        MDIO_CTRL_START |
        LINK_CTRL_L0S_EN |
        MDIO_CTRL_OP_READ;
    write_null_terminated_byte_array(&debug_output, " new ");
    write_hex_N_32(&debug_output, *MDIO_control_register);*/

    N_32 *txq = BARs[0] + REG_TXQ_CTRL;
    N_32 *rxq = BARs[0] + REG_RXQ_CTRL;
    N_32 *mac = BARs[0] + REG_MAC_CTRL;

    *txq |= TXQ_CTRL_EN;
    *rxq |= RXQ_CTRL_EN;
    *mac |= MAC_CTRL_TX_EN | MAC_CTRL_TX_FLOW |
            MAC_CTRL_RX_EN | MAC_CTRL_RX_FLOW |
            MAC_CTRL_BC_EN;
}