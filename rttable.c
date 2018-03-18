// A row struct for routing table.
typedef struct
{
	// destination Address
    in6_addr destAddr;

    // used if destination is network
    unsigned char prefixLength;

    // Next hop router address
    in6_addr nextHop;
	
	// output Interface ID
    unsigned int outIntfId;
} Ospfv3RoutingTableRow;

/// Routing table kept by ospf.
typedef struct
{
    int numRows;
    DataBuffer buffer;
} Ospfv3RoutingTable;





// Structure of an entity of forwarding table.
typedef
struct
{
	// destination Address
    in6_addr destAddr;

    // used if destination is network
    unsigned char prefixLength;
	
	// output Interface ID
    unsigned int outIntfId;
}
NetworkForwardingTableRow;

// Structure of forwarding table.
typedef
struct
{
    int size;                        // number of entries
    int allocatedSize;
    NetworkForwardingTableRow *row;  // allocation in Init function in Ip
}
NetworkForwardingTable;
