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

    // sub_C46A
    SetFunctionCmt(0xc46a, 
        "related to intro text", 1);

    // sub_253F8
    SetFunctionCmt(0x253f8, 
        "main trap 1/2 function, crucial to figure out", 1);

}
