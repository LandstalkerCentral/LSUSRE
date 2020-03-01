


#include <idc.idc>


static main(void){
    Message("\nPARSING DATA STRUCTURES INTO MACROS ...\n");
    
    parseMapWarps();
    parseSpritePalettes();
    
    Message("END OF PARSING.\n");    
}

/* To parse more thoroughly when properly documented */
static parseMapWarps(){
    auto addr, j, word0, word1, word2, word3;
    addr = 0x11CEA2;
    while(addr+8<0x11EA64){
        for(j=addr;j<addr+8;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,8,1);
        word0 = Word(addr);
        word1 = Word(addr+2);
        word2 = Word(addr+4);
        word3 = Word(addr+6);
        SetManualInsn(addr, form("mapWarp $%s, $%s, $%s, $%s", ltoa(word0,16), ltoa(word1,16), ltoa(word2,16), ltoa(word3,16)));
        addr = addr+8;
    }
}

static parseSpritePalettes(){
    auto addr, j, byte0, byte1;
    addr = 0x1A453A;
    while(addr+2<0x1A47E0){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,2,1);
        byte0 = Byte(addr);
        byte1 = Byte(addr+1);
        SetManualInsn(addr, form("spritePalette %s, %s", ltoa(byte0,10), ltoa(byte1,10)));
        addr = addr+2;
    }
}



/* 
 *  Makes sure byte at addr is
 *  clean for new formatting
 */
static undefineByte(addr){
        auto from;
        from = DfirstB(addr);
        /*
        while(from!=BADADDR){
            //Message(form("Removed DATA XRef at addr %a, from %a\n",addr, from));
      del_dref(from,addr);
      from=DnextB(addr,from);
        }        
        from = RfirstB(addr);
        while(from!=BADADDR){
            //Message(form("Removed Code XRrf at addr %a, from %a\n",addr, from));
      DelCodeXref(from,addr,1);
      from=RnextB(addr,from);      
        }    
        */            
        MakeUnkn(addr,DOUNK_DELNAMES);
        //MakeNameEx(addr,"",0);
        SetManualInsn(addr,"");
}
