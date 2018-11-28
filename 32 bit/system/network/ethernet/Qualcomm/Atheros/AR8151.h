#define MAC_ADDRESS_QUALCOMM_ATHEROS_AR8151 0x1488

#define GPHY_CONTROLLER_QUALCOMM_ATHEROS_AR8151 0x140C
#define LED_MODE_GPHY_CONTROLLER_QUALCOMM_ATHEROS_AR8151 0b00000010

#define REG_LINK_CTRL           0x68
#define LINK_CTRL_L0S_EN        0x01
#define LINK_CTRL_L1_EN         0x02
#define LINK_CTRL_EXT_SYNC  0x80

#define BIT(n) (1 << (n))

/* MDIO Control Register */
#define REG_MDIO_CTRL               0x1414
#define MDIO_CTRL_MODE_EXT      BIT(30)
#define MDIO_CTRL_POST_READ     BIT(29)
#define MDIO_CTRL_AP_EN         BIT(28)
#define MDIO_CTRL_BUSY          BIT(27)
#define MDIO_CTRL_CLK_SEL_MASK      0x7UL
#define MDIO_CTRL_CLK_SEL_SHIFT     24
#define MDIO_CTRL_CLK_25_4      0   /* 25MHz divide 4 */
#define MDIO_CTRL_CLK_25_6      2
#define MDIO_CTRL_CLK_25_8      3
#define MDIO_CTRL_CLK_25_10     4
#define MDIO_CTRL_CLK_25_32     5
#define MDIO_CTRL_CLK_25_64     6
#define MDIO_CTRL_CLK_25_128        7
#define MDIO_CTRL_START         BIT(23)
#define MDIO_CTRL_SPRES_PRMBL       BIT(22)
#define MDIO_CTRL_OP_READ       BIT(21) /* 1:read, 0:write */
#define MDIO_CTRL_REG_MASK      0x1FUL
#define MDIO_CTRL_REG_SHIFT     16
#define MDIO_CTRL_DATA_MASK     0xFFFFUL
#define MDIO_CTRL_DATA_SHIFT        0
#define MDIO_MAX_AC_TO  120 /* 1.2ms timeout for slow clk */

#define REG_TXQ_CTRL    0x1590
#define TXQ_CTRL_EN BIT(5)

#define REG_RXQ_CTRL 0x15A0
#define RXQ_CTRL_EN BIT(31)

#define REG_MAC_CTRL 0x1480
#define MAC_CTRL_RX_EN          BIT(1)
#define MAC_CTRL_TX_EN  BIT(0)
#define MAC_CTRL_RX_FLOW        BIT(3)
#define MAC_CTRL_TX_FLOW    BIT(2)
#define MAC_CTRL_BC_EN  BIT(26)


procedure initialize_Qualcomm_Atheros_AR8151_network_device (Network_Device *network_device, PCI_Device *device);


#include "AR8151.c"