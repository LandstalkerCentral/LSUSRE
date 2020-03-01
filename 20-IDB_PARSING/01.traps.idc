
/*
 *    PARSETRAP0 SCRIPT 
 *    This script will scan "TRAP #0" instructions 
 *  and parse the following word to add corresponding sound command 
 *  as a constant from an Enum, for easier code readability.
 * 
 *  TODO:
 *  Figure out and parse TRAP #1 and TRAP #2 commands.
 *
 */

#include <idc.idc>

static main(void) {

    Message("FIXING FUNCTION CHUNKS...\n");

    fixFChunks();

    Message("SCANNING TRAPS...\n");
    
    parseSoundTrap();
    Message("END OF TRAPS SCAN.\n");
    Batch(0);

}

/* MANUALLY FIX FUNCTION CHUNKS IMPROPERLY PARSED BECAUSE OF TRAPS */
static fixFChunks(){

    /* SF2 example
    // InitGame
    RemoveFchunk(0x70D2, 0x71CE);
    AppendFchunk(0x70D2, 0x71CE, 0x73FE);
    */
}

static parseSoundTrap(void) {

    Message("SCANNING TRAP 0...\n");
    
    scanTrap0();
    Message("\nDONE.\n");
    
    Message("END OF TRAP 0 SCAN.\n");

}



/* SOUND */

static scanTrap0(){

    auto addr; // current location
    auto parameter; // parameter found after TRAP 0
    auto action; 
    auto cont; // script continuation asked to user
    auto param;
    action = 0;
    cont = 1;
    addr=0;
    //action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
    if (action==-1) return;
    if (action==1){
        addr = ScreenEA();
    }
    Message(form("\nStarting from address 0x%s",ltoa(addr,16)));
    
    for(addr=FindBinary(addr+1,7,"4E 40");addr!=BADADDR;addr=FindBinary(addr+1,7,"4E 40")){

        //Jump(addr);
        if(GetFunctionAttr(addr-2, FUNCATTR_START)!=-1 || isCode(addr-2)){
        
            OpEnumEx(addr,0,GetEnum("Traps"),0);
            MakeWord(addr+2);
        
            parameter = Word(addr+2);

            //Message(form("\nBinary value 0x4E40 with parameter value 0x%s at address 0x%s in code.",ltoa(parameter,16),ltoa(addr,16)));
            
            param = "";
            
            if(parameter == 0x20
                    || (parameter >= 0xF0 &&  parameter <= 0xFF)
                    || (parameter >= 0xFFF0 &&  parameter <= 0xFFFF)){
                    OpEnumEx(addr+2,0,GetEnum("SoundCommands"),0);
                    param = GetConstName(GetConstEx(GetEnum("SoundCommands"),parameter,0,0));
            }
            else if(parameter >= 0 && parameter <= 0x30){
                    OpEnumEx(addr+2,0,GetEnum("Music"),0);
                    param = GetConstName(GetConstEx(GetEnum("Music"),parameter,0,0));
            }
            else if(parameter >= 0x41 && parameter <= 0x80){
                    OpEnumEx(addr+2,0,GetEnum("Sfx"),0);
                    param = GetConstName(GetConstEx(GetEnum("Sfx"),parameter,0,0));
            }    
            else{
                Message(form("\n%s: could not process trap 0 value %d",ltoa(addr,16),parameter));
                MakeUnkn(addr,DOUNK_DELNAMES);
                MakeUnkn(addr+1,DOUNK_DELNAMES);
                MakeUnkn(addr+2,DOUNK_DELNAMES);
                MakeUnkn(addr+3,DOUNK_DELNAMES);
                SetManualInsn(addr, "");
            }                    
            
            /* Macro formatting */
            if(param!=""){
              if(addr!=GetFunctionAttr(addr-2,FUNCATTR_START)){
                  MakeUnkn(addr,DOUNK_DELNAMES);
                  MakeUnkn(addr+1,DOUNK_DELNAMES);
                  MakeUnkn(addr+2,DOUNK_DELNAMES);
                  MakeUnkn(addr+3,DOUNK_DELNAMES);
                  MakeData(addr,FF_BYTE,4,1);
                  SetManualInsn(addr, form("sndCom  %s", param));
              }else{
                  MakeUnkn(addr+2,DOUNK_DELNAMES);
                  MakeUnkn(addr+3,DOUNK_DELNAMES);
                  MakeData(addr+2,FF_BYTE,2,1);
                  SetManualInsn(addr, " ");
                  SetManualInsn(addr+2, form("sndCom  %s", param));
              }
            }
            /*
            if(GetFunctionAttr(addr,FUNCATTR_START)==GetFunctionAttr(addr+4,FUNCATTR_START)){
                MakeUnkn(addr+4,DOUNK_SIMPLE);
            }
            if(GetFunctionAttr(addr,FUNCATTR_START)==GetFunctionAttr(addr+5,FUNCATTR_START)){
                MakeUnkn(addr+5,DOUNK_SIMPLE);
            }
            if(GetFunctionAttr(addr,FUNCATTR_START)==GetFunctionAttr(addr+6,FUNCATTR_START)){
                MakeUnkn(addr+6,DOUNK_SIMPLE);
            }
            */
            MakeCode(addr+4);
            
            //cont = AskYN(1,"Continue ?");
            //if (cont==-1 || cont==0) return;    
        }
        else{
            Message(form("\n0x%s: Binary value 0x4E40 with parameter value 0x%s not in code",ltoa(addr,16),ltoa(Word(addr+2),16)));
        }
    }
    
}



