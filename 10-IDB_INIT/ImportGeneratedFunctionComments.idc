static main()
{
    // sub_2F0
    SetFunctionCmt(0x2f0, 
        "related to decompression", 1);

    // sub_2F6
    SetFunctionCmt(0x2f6, 
        "could also be related to decompression", 1);

    // j_GenerateRandomNumber
    SetFunctionCmt(0x362, 
        "d6=range", 1);

    // Sleep
    SetFunctionCmt(0xb7a, 
        "d0=frames", 1);

    // ApplyImmediateVramDMA
    SetFunctionCmt(0xd22, 
        "A0=Source, A1=Destination, D0=Length, D1=Auto-increment", 1);

    // ApplyVIntVramDMA
    SetFunctionCmt(0xdd6, 
        "A0=Source, A1=Destination, D0=Length, D1=Auto-increment", 1);

    // ApplyVramDMAFill
    SetFunctionCmt(0xf42, 
        "D0=Destination, D1=Length, D2=Filler value", 1);

    // GenerateRandomNumber
    SetFunctionCmt(0x1164, 
        "d6=range", 1);

    // sub_468A
    SetFunctionCmt(0x468a, 
        "Loads sprite\n\
d0=sprite index", 1);

    // sub_9D36
    SetFunctionCmt(0x9d36, 
        "related to animated map tileset", 1);

    // sub_9EF8
    SetFunctionCmt(0x9ef8, 
        "related to map warp data", 1);

    // sub_9F1C
    SetFunctionCmt(0x9f1c, 
        "uses map warp data", 1);

    // sub_C46A
    SetFunctionCmt(0xc46a, 
        "related to intro text", 1);

    // sub_F13A
    SetFunctionCmt(0xf13a, 
        "loads Nigel sprite in game save screen ?", 1);

    // sub_FA24
    SetFunctionCmt(0xfa24, 
        "Game save menu behaviour", 1);

    // sub_253F8
    SetFunctionCmt(0x253f8, 
        "main trap 1/2 function, crucial to figure out", 1);

    // GetOwnedItemQuantityEnriched
    SetFunctionCmt(0x29192, 
        "d0=item index | d1=quantity owned, d2=can carry multiple units", 1);

    // CheckAndSetOwnedItemQuantity
    SetFunctionCmt(0x291b6, 
        "d0=item index, d1=quantity owned", 1);

    // ConsumeOneItem
    SetFunctionCmt(0x2921c, 
        "d0=item index", 1);

    // GetOwnedItemQuantity
    SetFunctionCmt(0x29260, 
        "d0=item index | d1=quantity owned", 1);

    // SetOwnedItemQuantity
    SetFunctionCmt(0x29288, 
        "d0=item index, d1=item quantity", 1);

    // GetMaxQuantityForItem
    SetFunctionCmt(0x292b8, 
        "d0=item index | d1=max quantity for item", 1);

    // GetItemDescriptionAddress
    SetFunctionCmt(0x292f4, 
        "d0=item index | a0=item description address", 1);

}
