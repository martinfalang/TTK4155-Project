# Library modules

The `lib` folder includes all files that are shared between Node1 and Node2 in this project. The library files uses preprocessor directives to ensure that correct versions of functions are compiled for the correct microcontroller.

The included files are
* `spi`: Includes SPI functions for both nodes
* `timer`: Includes timing functions for both nodes. These include timeout checks for 1, 6, 10 and 60Hz for general timing use throughout the programs of both nodes
* `uart`: Functions for setting up uart communication on both nodes, and for redirecting `printf` to use uart
* `mcp2515`: Libraries for interfacing with MCP2515 standalone CAN controller
* `mcp2515_defines`: Includes addresses to useful registers in the MCP2515
* `can`: General can library for both nodes. Uses MCP2515 as CAN controller
* `can_message_defs`: Defines different CAN message formats
* `defines`: Includes the CPU frequency for both nodes
* `heartbeat`: Simple library for toggling a LED
